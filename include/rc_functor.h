/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_functor.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_FUNCTOR_H_
#define _RC_CPLUS_INCLUDE_RC_FUNCTOR_H_

#include "rc_common.h"

namespace crtc {

template <typename T>
class CRTC_EXPORT Functor;

template <typename R, typename... Args>
class CRTC_EXPORT Functor<R(Args...)> {
 public:
  enum Flags {
    kNone = 1 << 1,
    kOnce = 1 << 2,
  };

  explicit Functor() : _flags(kNone) {}
  virtual ~Functor() {}

  Functor(const Functor<R(Args...)>& functor, const Functor<void()>& notifier)
      : _flags(kOnce),
        _callback(Let<VerifyWrap<void>>::New(functor, notifier)) {}
  Functor(const Functor<R(Args...)>& functor)
      : _flags(functor._flags), _callback(functor._callback) {}
  Functor(Functor&& functor)
      : _flags(functor._flags), _callback(std::move(functor._callback)) {}

  template <class T>
  inline Functor(const T& functor, Flags flags = kNone)
      : _flags(flags), _callback(Let<Wrap<T>>::New(functor)) {}
  template <class Object, class Method>
  inline Functor(Object* object, const Method& method, Flags flags = kNone)
      : _flags(flags),
        _callback(Let<ObjectWrap<Object, Method>>::New(object, method)) {}
  template <class Object, class Method>
  inline Functor(const Let<Object>& object,
                 const Method& method,
                 Flags flags = kNone)
      : _flags(flags),
        _callback(Let<LetWrap<Object, Method>>::New(object, method)) {}

  inline R operator()(Args... args) const {
    if (!_callback.IsEmpty()) {
      Let<Callback> callback = _callback;

      if (_flags & kOnce) {
        _callback.Dispose();
      }

      return callback->Call(std::move(args)...);
    }

    return R();
  }

  inline Functor<R(Args...)>& operator=(const Functor<R(Args...)>& functor) {
    _flags = functor._flags;
    _callback = std::move(functor._callback);
    return *this;
  }

  inline bool IsEmpty() const { return _callback.IsEmpty(); }

  operator bool() const { return !_callback.IsEmpty(); }

  inline void Dispose() const { _callback.Dispose(); }

 private:
  class Callback : virtual public Reference {
    CRTC_PRIVATE(Callback);
    friend class Let<Callback>;

   public:
    virtual R Call(Args&&... args) const = 0;

   protected:
    explicit Callback() {}
    ~Callback() override {}
  };

  template <class T>
  class Wrap : public Callback {
    CRTC_PRIVATE(Wrap);
    friend class Let<Wrap>;

   public:
    inline R Call(Args&&... args) const override {
      return _functor(std::forward<Args>(args)...);
    }

   protected:
    explicit Wrap(const T& functor) : _functor(functor) {}
    ~Wrap() override {}

    T _functor;
  };

  template <class Object, class Method>
  class ObjectWrap : public Callback {
    CRTC_PRIVATE(ObjectWrap);
    friend class Let<ObjectWrap>;

   public:
    inline R Call(Args&&... args) const override {
      if (_object) {
        return (_object->*_method)(std::forward<Args>(args)...);
      }

      return R();
    }

   protected:
    explicit ObjectWrap(Object* object, const Method& method)
        : _object(object), _method(method) {}
    ~ObjectWrap() override {}

    Object* _object;
    Method _method;
  };

  template <class Object, class Method>
  class LetWrap : public Callback {
    CRTC_PRIVATE(LetWrap);
    friend class Let<LetWrap>;

   public:
    inline R Call(Args&&... args) const override {
      if (!_object.IsEmpty()) {
        return (_object->*_method)(std::forward<Args>(args)...);
      }

      return R();
    }

   protected:
    explicit LetWrap(const Let<Object>& object, const Method& method)
        : _object(object), _method(method) {}
    ~LetWrap() override {}

    Let<Object> _object;
    Method _method;
  };

  template <class Type = void>
  class VerifyWrap : public Callback {
    CRTC_PRIVATE(VerifyWrap);
    friend class Let<VerifyWrap>;

   public:
    inline R Call(Args&&... args) const override {
      _notifier.Dispose();
      return _functor(std::forward<Args>(args)...);
    }

   protected:
    explicit VerifyWrap(const Functor<R(Args...)>& functor,
                        const Functor<Type()>& notifier)
        : _functor(functor), _notifier(notifier) {}

    ~VerifyWrap() override { _notifier(); }

    Functor<R(Args...)> _functor;
    Functor<Type()> _notifier;
  };

  Flags _flags;
  Let<Callback> _callback;
};

typedef Functor<void()> Callback;

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_FUNCTOR_H_