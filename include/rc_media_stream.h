/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_media_stream.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_MEDIA_STREAM_H_
#define _RC_CPLUS_INCLUDE_RC_MEDIA_STREAM_H_

#include "rc_common.h"

#include "rc_error.h"
#include "rc_functor.h"
#include "rc_let.h"

namespace crtc {


//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack

class MediaStreamTrack : virtual public Reference {
  CRTC_PRIVATE(MediaStreamTrack);

 public:
  enum Type {
    kAudio,
    kVideo,
  };

  enum State {
    kLive,
    kEnded,
  };

  virtual bool Enabled() const = 0;
  virtual bool Muted() const = 0;
  virtual bool Remote() const = 0;
  virtual std::string Id() const = 0;

  virtual Type Kind() const = 0;
  virtual State ReadyState() const = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack/clone

  virtual Let<MediaStreamTrack> Clone() = 0;

  Callback onstarted;
  Callback onended;
  Callback onmute;
  Callback onunmute;

 protected:
  explicit MediaStreamTrack();
  ~MediaStreamTrack() override;
};

typedef std::vector<Let<MediaStreamTrack>> MediaStreamTracks;

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaStream

class MediaStream : virtual public Reference {
  CRTC_PRIVATE(MediaStream);

 public:
  virtual std::string Id() const = 0;

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaStream/addTrack

  virtual void AddTrack(const Let<MediaStreamTrack>& track) = 0;
  virtual void RemoveTrack(const Let<MediaStreamTrack>& track) = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/MediaStream/getTrackById

  virtual Let<MediaStreamTrack> GetTrackById(const std::string& id) const = 0;

  virtual MediaStreamTracks GetAudioTracks() const = 0;
  virtual MediaStreamTracks GetVideoTracks() const = 0;

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaStream/clone

  virtual Let<MediaStream> Clone() = 0;

  Functor<void(const Let<MediaStreamTrack>& track)> onaddtrack;
  Functor<void(const Let<MediaStreamTrack>& track)> onremovetrack;

 protected:
  explicit MediaStream();
  ~MediaStream() override;
};

typedef std::vector<Let<MediaStream>> MediaStreams;
}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_MEDIA_STREAM_H_