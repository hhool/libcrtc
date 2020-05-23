/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_atomic.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_ATOMIC_H_
#define _RC_CPLUS_INCLUDE_RC_ATOMIC_H_

#include "rc_common.h"
namespace crtc {

class CRTC_EXPORT Atomic {
    CRTC_STATIC(Atomic);

  public:
    static int Increment(volatile int *arg);
    static int Decrement(volatile int *arg);
    static int AcquireLoad(volatile int *arg);
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_ATOMIC_H_