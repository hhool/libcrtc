
#ifndef CRTC_EVENT_TIMER_WRAPPER_H
#define CRTC_EVENT_TIMER_WRAPPER_H


#include "system_wrappers/include/event_wrapper.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace webrtc {
  class EventWrapper;
}

namespace crtc {
class EventTimerWrapper : public webrtc::EventWrapper {
 public:
  static EventTimerWrapper* Create();

  // Starts a timer that will call a non-sticky version of Set() either once
  // or periodically. If the timer is periodic it ensures that there is no
  // drift over time relative to the system clock.
  //
  // |time| is in milliseconds.
  virtual bool StartTimer(bool periodic, unsigned long time) = 0;

  virtual bool StopTimer() = 0;
};
}  // namespace crtc

#endif