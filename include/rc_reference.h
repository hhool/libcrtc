/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_reference.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_REFERENCE_H_
#define _RC_CPLUS_INCLUDE_RC_REFERENCE_H_

#include "rc_common.h"

namespace crtc {

class CRTC_EXPORT Reference {
  template <class T>
  friend class Let;

 protected:
  virtual ~Reference() {}

  virtual int AddRef() const = 0;
  virtual int RemoveRef() const = 0;
  virtual int RefCount() const = 0;
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_REFERENCE_H_