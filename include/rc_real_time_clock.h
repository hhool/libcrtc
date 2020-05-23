/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_real_time_clock.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_REAL_TIME_CLOCK_H_
#define _RC_CPLUS_INCLUDE_RC_REAL_TIME_CLOCK_H_

#include "rc_common.h"

namespace crtc {

class CRTC_EXPORT RealTimeClock : virtual public Reference {
  CRTC_PRIVATE(RealTimeClock);

 public:
  static Let<RealTimeClock> New(const Callback& runnable = Callback());

  virtual void Start(uint32_t interval_ms = 0) = 0;
  virtual void Stop() = 0;

 protected:
  explicit RealTimeClock() {}
  ~RealTimeClock() override {}
};

}  // namespace crtc

#endif  //_RC_CPLUS_INCLUDE_RC_REAL_TIME_CLOCK_H_