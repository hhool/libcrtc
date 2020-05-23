/*
* The MIT License (MIT)
*
* Copyright (c) 2017 vmolsa <ville.molsa@gmail.com> (http://github.com/vmolsa)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#include "rc_crtc.h"
#include "async.h"
#include "worker.h"

#include "rtc_base/thread.h"
#include "rtc_base/async_invoker.h"

namespace crtc {

rtc::AsyncInvoker* _async;

void AsyncInternal::Init() {
  _async = new rtc::AsyncInvoker();
}

void AsyncInternal::Dispose() {
  delete _async;
}

void Async::Call(Functor<void()> callback, int delay, Let<Worker> ptr) {
  Let<Event> event = Event::New();
  Let<WorkerInternal> worker(ptr);
  rtc::Thread* target = (!worker.IsEmpty()) ? worker : rtc::Thread::Current();

  if (delay > 0) {
    _async->AsyncInvokeDelayed<void>(RTC_FROM_HERE, target, [worker, callback, event]() mutable {
      callback();
    }, delay);
  } else {
    _async->AsyncInvoke<void>(RTC_FROM_HERE, target, [worker, callback, event]() mutable {
      callback();
    });
  }
}
}  // namespace crtc