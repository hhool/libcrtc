/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_array_bffer.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_ARRAY_BUFFER_H_
#define _RC_CPLUS_INCLUDE_RC_ARRAY_BUFFER_H_

#include "rc_common.h"
namespace crtc {

//TODO(hhool):https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_Objects/ArrayBuffer

class CRTC_EXPORT ArrayBuffer : virtual public Reference {
    CRTC_PRIVATE(ArrayBuffer);

  public:
    static Let<ArrayBuffer> New(size_t byteLength = 0);
    static Let<ArrayBuffer> New(const std::string &data);
    static Let<ArrayBuffer> New(const uint8_t *data, size_t byteLength = 0);

    virtual size_t ByteLength() const = 0;

    virtual Let<ArrayBuffer> Slice(size_t begin = 0, size_t end = 0) const = 0;

    virtual uint8_t *Data() = 0;
    virtual const uint8_t *Data() const = 0;

    virtual std::string ToString() const = 0;

  protected:
    explicit ArrayBuffer() { }
    ~ArrayBuffer() override { }
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_ARRAY_BUFFER_H_