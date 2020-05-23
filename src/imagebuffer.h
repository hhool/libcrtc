/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 vmolsa <ville.molsa@gmail.com> (http://github.com/vmolsa)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef CRTC_IMAGEBUFFER_H
#define CRTC_IMAGEBUFFER_H

#include "rc_crtc.h"
#include "arraybuffer.h"

#include "common_video/include/video_frame_buffer.h"
#include "rtc_base/ref_count.h"

namespace crtc {
class ImageBufferInternal : public ImageBuffer, public ArrayBufferInternal {
  friend class Let<ImageBufferInternal>;

 public:
  static Let<ImageBuffer> New(const Let<ArrayBuffer>& buffer,
                              int width,
                              int height);
  static Let<ImageBuffer> New(int width = 0, int height = 0);

  int Width() const override;
  int Height() const override;

  const uint8_t* DataY() const override;
  const uint8_t* DataU() const override;
  const uint8_t* DataV() const override;

  int StrideY() const override;
  int StrideU() const override;
  int StrideV() const override;

  size_t ByteLength() const override;

  Let<ArrayBuffer> Slice(size_t begin = 0, size_t end = 0) const override;

  uint8_t* Data() override;
  const uint8_t* Data() const override;

  std::string ToString() const override;

 protected:
  explicit ImageBufferInternal(const Let<ArrayBuffer>& buffer,
                               int width,
                               int height);
  ImageBufferInternal(int width = 0, int height = 0);
  ~ImageBufferInternal() override;

  int _width;
  int _height;

  const uint8_t* _y;
  const uint8_t* _u;
  const uint8_t* _v;
};

class WrapImageBuffer : public webrtc::VideoFrameBuffer {
 public:
  static rtc::scoped_refptr<webrtc::VideoFrameBuffer> New(
      const Let<ImageBuffer>& source);

  // Inherited via VideoFrameBuffer
  virtual rtc::scoped_refptr<webrtc::I420BufferInterface> ToI420() override;
  webrtc::VideoFrameBuffer::Type type() const override;

  int width() const override;
  int height() const override;

 protected:
  explicit WrapImageBuffer(const Let<ImageBuffer>& source);
  ~WrapImageBuffer() override;

  Let<ImageBuffer> _source;

};

class WrapVideoFrameBuffer : public ImageBuffer {
  friend class Let<WrapVideoFrameBuffer>;

 public:
  static Let<ImageBuffer> New(
      const rtc::scoped_refptr<webrtc::VideoFrameBuffer>& vfb);

  int Width() const override;
  int Height() const override;

  const uint8_t* DataY() const override;
  const uint8_t* DataU() const override;
  const uint8_t* DataV() const override;

  int StrideY() const override;
  int StrideU() const override;
  int StrideV() const override;

  size_t ByteLength() const override;

  Let<ArrayBuffer> Slice(size_t begin = 0, size_t end = 0) const override;

  uint8_t* Data() override;
  const uint8_t* Data() const override;

  std::string ToString() const override;

 protected:
  explicit WrapVideoFrameBuffer(
      const rtc::scoped_refptr<webrtc::VideoFrameBuffer>& source);
  ~WrapVideoFrameBuffer() override;

  rtc::scoped_refptr<webrtc::VideoFrameBuffer> _vfb;
};

class WrapBufferToVideoFrameBuffer : public webrtc::VideoFrameBuffer {
 public:
  static rtc::scoped_refptr<webrtc::VideoFrameBuffer>
  New(const Let<ArrayBuffer>& source, int width, int height);

  // Inherited via VideoFrameBuffer
  webrtc::VideoFrameBuffer::Type type() const override;
  int width() const override;
  int height() const override;
  virtual rtc::scoped_refptr<webrtc::I420BufferInterface> ToI420() override;

 protected:
  explicit WrapBufferToVideoFrameBuffer(const Let<ArrayBuffer>& source,
                                        int width,
                                        int height);
  ~WrapBufferToVideoFrameBuffer() override;

  Let<ArrayBuffer> _source;

  int _width;
  int _height;

  const uint8_t* _y;
  const uint8_t* _u;
  const uint8_t* _v;

};
};  // namespace crtc

#endif