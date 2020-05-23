/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_async.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_ASYNC_H_
#define _RC_CPLUS_INCLUDE_RC_ASYNC_H_

#include "rc_common.h"
namespace crtc {

class CRTC_EXPORT Async {
  CRTC_STATIC(Async);

 public:
  static void Call(Callback callback,
                   int delay = 0,
                   Let<Worker> worker = Worker::This());
};

//TODO(hhool):https://developer.mozilla.org/en/docs/Web/API/Window/SetImmediate

template <typename F, typename... Args>
static inline void SetImmediate(F&& func, Args... args) {
  Functor<void(Args...)> callback(func);

  Async::Call(
      Callback([=]() { callback(args...); }, [=]() { callback(args...); }));
}

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/WindowTimers/setTimeout

template <typename F, typename... Args>
static inline void SetTimeout(F&& func, int delay, Args... args) {
  Functor<void(Args... args)> callback(func);

  Async::Call(
      Callback([=]() { callback(args...); }, [=]() { callback(args...); }),
      (delay > 0) ? delay : 0);
}
}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_ASYNC_H_