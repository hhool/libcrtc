/*
#
# Copyright 2020, rc inc
# author: hhool
# atomic.cc
# 2020-05-22
#
*/


#include "rc_atomic.h"
#include "rtc_base/atomic_ops.h"

namespace crtc {

int Atomic::Increment(volatile int *arg) {
  return rtc::AtomicOps::Increment(arg);
}

int Atomic::Decrement(volatile int *arg) {
  return rtc::AtomicOps::Decrement(arg);
}

int Atomic::AcquireLoad(volatile int *arg) {
  return rtc::AtomicOps::AcquireLoad(arg);
}
}