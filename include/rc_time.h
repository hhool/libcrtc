/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_time.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_TIME_H_
#define _RC_CPLUS_INCLUDE_RC_TIME_H_

#include "rc_common.h"

namespace crtc {

class CRTC_EXPORT Time {
  CRTC_STATIC(Time);

 public:
  static int64_t Now();  // returns current time in milliseconds
  static int64_t Diff(int64_t begin,
                      int64_t end = Now());  // returns milliseconds
  static double Since(int64_t begin, int64_t end = Now());  // returns seconds
};

}  // namespace crtc

#endif  //_RC_CPLUS_INCLUDE_RC_TIME_H_