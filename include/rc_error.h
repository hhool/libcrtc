/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_error.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_ERROR_H_
#define _RC_CPLUS_INCLUDE_RC_ERROR_H_

#include "rc_common.h"
#include "rc_let.h"
#include "rc_functor.h"

namespace crtc {

/// \sa
/// https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_Objects/Error

class CRTC_EXPORT Error : virtual public Reference {
 public:
  static Let<Error> New(std::string message,
                        std::string fileName = __FILE__,
                        int lineNumber = __LINE__);

  virtual std::string Message() const = 0;
  virtual std::string FileName() const = 0;
  virtual int LineNumber() const = 0;

  virtual std::string ToString() const = 0;

 protected:
  explicit Error() {}
  ~Error() override {}
};

typedef Functor<void(const Let<Error> &error)> ErrorCallback;
}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_ERROR_H_