
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

#ifndef CRTC_MEDIADEVICES_H
#define CRTC_MEDIADEVICES_H

#include "rc_crtc.h"
#include "mediastream.h"
#include "mediastreamtrack.h"

#include "api/peer_connection_interface.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/video_capture/video_capture_factory.h"

namespace crtc {
//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/LongRange

/*
typedef struct {
  int max;
  int min;
} LongRange;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/ConstrainLong

/*
typedef struct : LongRange {
  int exact;
  int ideal;
} ConstrainLong;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/ConstrainBoolean

/*
typedef struct {
  bool exact;
  bool ideal;
} ConstrainBoolean;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/DoubleRange

/*
typedef struct {
  double max;
  double min;
} DoubleRange;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/ConstrainDouble

/*
typedef struct : DoubleRange {
  double exact;
  double ideal;
} ConstrainDouble;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/ConstrainDOMString

/*
typedef struct {
  std::string exact;
  std::string ideal;
} ConstrainString;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints

/*
typedef struct {
  ConstrainString deviceId;
  ConstrainString groupId;
  ConstrainLong channelCount;
  ConstrainBoolean echoCancellation;
  DoubleRange latency;
  ConstrainLong sampleRate;
  ConstrainLong sampleSize;
  ConstrainDouble volume;
  ConstrainDouble aspectRatio;
  ConstrainString facingMode;
  ConstrainDouble frameRate;
  ConstrainLong height;
  ConstrainLong width;
} MediaTrackConstraints;
*/

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackSettings

/*
typedef struct {
  enum FacingMode {
    kUser,
    kEnvironment,
    kLeft,
    kRight,
  };

  std::string deviceId;
  std::string groupId;

  bool echoCancellation;

  double latency;
  double volume;
  double aspectRatio;
  double frameRate;

  int channelCount;
  int sampleRate;
  int sampleSize;
  int height;
  int width;

  FacingMode facingMode;
} MediaTrackSettings;

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaDeviceInfo

typedef struct {
  enum Kind {
    kVideoInput,
    kAudioInput,
    kAudioOutput,
  };

  std::string deviceId;
  std::string groupId;
  std::string label;
  Kind kind;
} MediaDeviceInfo;

typedef std::vector<MediaDeviceInfo> MediaDeviceInfos;

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamConstraints

typedef struct {
  bool enableVideo;
  bool enableAudio;
  
  std::string videoSourceId;
  std::string audioSourceId;

  //MediaTrackConstraints video;
  //MediaTrackConstraints audio;
} MediaStreamConstraints;

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices

class CRTC_EXPORT MediaDevices {
  public:
    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices/enumerateDevices

    static Let<Promise<MediaDeviceInfos>> EnumerateDevices();

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices/getSupportedConstraints

    // static Let<Promise<void>> GetSupportedConstraints();

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices/getUserMedia

    static Let<Promise<Let<MediaStream>>> GetUserMedia();
    static Let<Promise<Let<MediaStream>>> GetUserMedia(const MediaStreamConstraints &constraints);
};
*/

class MediaDevicesInternal {
  public:
    static void Init();

    static std::unique_ptr<rtc::Thread> network_thread;
    static std::unique_ptr<rtc::Thread> worker_thread;
    static rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> media_factory;
    static rtc::scoped_refptr<webrtc::AudioDeviceModule> audio_device;
    static std::unique_ptr<webrtc::VideoCaptureModule::DeviceInfo> video_device;
    
};
}
#endif