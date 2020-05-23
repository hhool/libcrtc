/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_worker.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_WORKER_H_
#define _RC_CPLUS_INCLUDE_RC_WORKER_H_

#include "rc_common.h"

namespace crtc {

class CRTC_EXPORT Worker : virtual public Reference {
  CRTC_PRIVATE(Worker);

 public:
  static Let<Worker> New(const Callback& runnable = Callback());
  static Let<Worker> This();

 protected:
  explicit Worker() {}
  ~Worker() override {}
};

}  // namespace crtc

#endif  //_RC_CPLUS_INCLUDE_RC_WORKER_H_