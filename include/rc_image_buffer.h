/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_image_buffer.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_IMAGE_BUFFER_H_
#define _RC_CPLUS_INCLUDE_RC_IMAGE_BUFFER_H_

#include "rc_common.h"
#include "rc_let.h"

namespace crtc {

class CRTC_EXPORT ImageBuffer : public ArrayBuffer {
    CRTC_PRIVATE(ImageBuffer);

  public:
    static Let<ImageBuffer> New(int width, int height);
    static Let<ImageBuffer> New(const Let<ArrayBuffer> &buffer, int width, int height);

    static size_t ByteLength(int height, int stride_y, int stride_u, int stride_v);
    static size_t ByteLength(int width, int height);

    virtual int Width() const = 0;
    virtual int Height() const = 0;

    virtual const uint8_t* DataY() const = 0;
    virtual const uint8_t* DataU() const = 0;
    virtual const uint8_t* DataV() const = 0;

    virtual int StrideY() const = 0;
    virtual int StrideU() const = 0;
    virtual int StrideV() const = 0;

  protected:
    explicit ImageBuffer() { }
    ~ImageBuffer() override { }
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_IMAGE_BUFFER_H_