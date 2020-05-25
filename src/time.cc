/*
#
# Copyright 2020, rc inc
# author: hhool
# time.cc
# 2020-05-22
#
*/

#include "rc_time.h"
#include "rtc_base/time_utils.h"

namespace crtc {

int64_t Time::Now() {
  return rtc::TimeMillis();
}

int64_t Time::Diff(int64_t begin, int64_t end) {
  return end - begin; 
}

double Time::Since(int64_t begin, int64_t end) {
  return static_cast<double>(Time::Diff(begin, end)) / 1000;
}
}