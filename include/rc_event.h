/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_event.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_EVENT_H_
#define _RC_CPLUS_INCLUDE_RC_EVENT_H_

#include "rc_common.h"
namespace crtc {

class CRTC_EXPORT Event : virtual public Reference {
  CRTC_PRIVATE(Event);
  friend class crtc::Let<Event>;

 public:
  static crtc::Let<crtc::Event> New();

 protected:
  explicit Event();
  ~Event() override;
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_EVENT_H_