/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_promise.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_PROMISE_H_
#define _RC_CPLUS_INCLUDE_RC_PROMISE_H_

#include "rc_common.h"
#include "rc_functor.h"
#include "rc_let.h"
#include "rc_error.h"

namespace crtc {

//TODO(hhool):https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_Objects/Promise

template <typename... Args> class Promise : virtual public Reference {
    CRTC_PRIVATE(Promise<Args...>);
    friend class Let<Promise<Args...>>;

  public:
    typedef Functor<void(Args...)> FullFilledCallback;
    typedef Callback FinallyCallback;
    typedef ErrorCallback RejectedCallback;
    typedef Functor<void(const FullFilledCallback &resolve, const RejectedCallback &reject)> ExecutorCallback;

    inline static Let<Promise<Args...>> New(const ExecutorCallback &executor, const Let<Worker> &worker = Worker::This()) {
      Let<Promise<Args...>> self = Let<Promise<Args...>>::New();

      RejectedCallback reject([=](const Let<Error> &error) {
        if (!self.IsEmpty()) {
          for (const auto &callback: self->_onreject) {
            callback(error);
          }

          for (const auto &callback: self->_onfinally) {
            callback();
          }

          self->_onfinally.clear();
          self->_onreject.clear();
          self->_onresolve.clear();

          self.Dispose();
        }
      });

      RejectedCallback asyncReject([=](const Let<Error> &error) {
        Async::Call(Callback([=]() {
          reject(error);
        }, [=]() {
          reject(error);
        }), 0, worker);
      });

      FullFilledCallback resolve([=](Args... args) {
        Async::Call(Callback([=]() {
          if (!self.IsEmpty()) {
            for (const auto &callback: self->_onresolve) {
              callback(std::move(args)...);
            }

            for (const auto &callback: self->_onfinally) {
              callback();
            }

            self->_onfinally.clear();
            self->_onreject.clear();
            self->_onresolve.clear();

            self.Dispose();
          }
        }, [=]() {
          asyncReject(Error::New("Reference Lost.", __FILE__, __LINE__));
        }), 0, worker);
      }, [=]() {
        asyncReject(Error::New("Reference Lost.", __FILE__, __LINE__));
      });

      if (!executor.IsEmpty()) {
        executor(resolve, asyncReject);
      } else {
        asyncReject(Error::New("Invalid Executor Callback.", __FILE__, __LINE__));
      }

      return self;
    }

    inline Let<Promise<Args...>> Then(const FullFilledCallback &callback) {
      _onresolve.push_back(callback);
      return this;
    }

    inline Let<Promise<Args...>> Catch(const RejectedCallback &callback) {
      _onreject.push_back(callback);
      return this;
    }

    inline Let<Promise<Args...>> Finally(const FinallyCallback &callback) {
      _onfinally.push_back(callback);
      return this;
    }

  private:
    std::vector<FullFilledCallback> _onresolve;
    std::vector<RejectedCallback> _onreject;
    std::vector<FinallyCallback> _onfinally;

  protected:
    explicit Promise() { }
    ~Promise() override { }
};

template<> class Promise<void> : public Promise<> { };

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_PROMISE_H_