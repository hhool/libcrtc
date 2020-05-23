/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_audio.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_AUDIO_H_
#define _RC_CPLUS_INCLUDE_RC_AUDIO_H_

#include "rc_common.h"
#include "rc_let.h"

namespace crtc {

class CRTC_EXPORT AudioBuffer : virtual public ArrayBuffer {
  CRTC_PRIVATE(AudioBuffer);

 public:
  static Let<AudioBuffer> New(int channels = 2,
                              int sampleRate = 44100,
                              int bitsPerSample = 8,
                              int frames = 1);
  static Let<AudioBuffer> New(const Let<ArrayBuffer>& buffer,
                              int channels = 2,
                              int sampleRate = 44100,
                              int bitsPerSample = 8,
                              int frames = 1);

  virtual int Channels() const = 0;
  virtual int SampleRate() const = 0;
  virtual int BitsPerSample() const = 0;
  virtual int Frames() const = 0;

 protected:
  explicit AudioBuffer() {}
  ~AudioBuffer() override {}
};

class CRTC_EXPORT AudioSource : virtual public MediaStream {
  CRTC_PRIVATE(AudioSource);

 public:
  static Let<AudioSource> New();

  virtual bool IsRunning() const = 0;
  virtual void Stop() = 0;

  virtual void Write(const Let<AudioBuffer>& buffer,
                     ErrorCallback callback = ErrorCallback()) = 0;

  Callback ondrain;

 protected:
  explicit AudioSource();
  ~AudioSource() override;
};

class CRTC_EXPORT AudioSink : virtual public MediaStreamTrack {
  CRTC_PRIVATE(AudioSink);

 public:
  static Let<AudioSink> New(const Let<MediaStreamTrack>& track);

  virtual bool IsRunning() const = 0;
  virtual void Stop() = 0;

  Functor<void(const Let<AudioBuffer>& buffer)> ondata;

 protected:
  explicit AudioSink();
  ~AudioSink() override;
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_AUDIO_H_