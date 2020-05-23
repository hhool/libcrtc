/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_video.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_VIDEO_H_
#define _RC_CPLUS_INCLUDE_RC_VIDEO_H_

#include "rc_common.h"
#include "rc_let.h"
#include "rc_image_buffer.h"

namespace crtc {

class CRTC_EXPORT VideoSource : virtual public MediaStream {
  CRTC_PRIVATE(VideoSource);

 public:
  static Let<VideoSource> New(int width = 1280,
                              int height = 720,
                              float fps = 30);

  virtual bool IsRunning() const = 0;
  virtual void Stop() = 0;

  virtual int Width() const = 0;
  virtual int Height() const = 0;
  virtual float Fps() const = 0;

  virtual void Write(const Let<ImageBuffer>& frame,
                     ErrorCallback callback = ErrorCallback()) = 0;

  Callback ondrain;

 protected:
  explicit VideoSource();
  ~VideoSource() override;
};

class CRTC_EXPORT VideoSink : virtual public MediaStreamTrack {
  CRTC_PRIVATE(VideoSink);

 public:
  static Let<VideoSink> New(const Let<MediaStreamTrack>& track);

  virtual bool IsRunning() const = 0;
  virtual void Stop() = 0;

  Functor<void(const Let<ImageBuffer>& frame)> ondata;

 protected:
  explicit VideoSink();
  ~VideoSink() override;
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_VIDEO_H_