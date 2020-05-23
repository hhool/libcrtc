/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef CRTC_EVENT_TIMER_WIN_H_
#define CRTC_EVENT_TIMER_WIN_H_

#include <windows.h>

#include "event_timer_wrapper.h"

namespace crtc {

class EventTimerWin : public EventTimerWrapper {
 public:
  EventTimerWin();
  virtual ~EventTimerWin();

  virtual webrtc::EventTypeWrapper Wait(unsigned long max_time) override;
  virtual bool Set() override;

  virtual bool StartTimer(bool periodic, unsigned long time) override;
  virtual bool StopTimer() override;

 private:
  HANDLE event_;
  uint32_t timerID_;
};

}  // namespace crtc

#endif  // CRTC_EVENT_TIMER_WIN_H_
