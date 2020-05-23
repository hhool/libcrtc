/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_data_channel.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_DATA_CHANNEL_H_
#define _RC_CPLUS_INCLUDE_RC_DATA_CHANNEL_H_

#include "rc_common.h"
#include "rc_let.h"

namespace crtc {

//TODO(hhool):https://developer.mozilla.org/en/docs/Web/API/RTCDataChannel

class CRTC_EXPORT RTCDataChannel : virtual public Reference {
  CRTC_PRIVATE(RTCDataChannel);

 public:
  typedef Functor<void(const Let<ArrayBuffer>& buffer, bool binary)>
      MessageCallback;

  enum State { kConnecting, kOpen, kClosing, kClosed };

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/id

  virtual int Id() = 0;

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/label

  virtual std::string Label() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/bufferedAmount

  virtual uint64_t BufferedAmount() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/bufferedAmountLowThreshold

  virtual uint64_t BufferedAmountLowThreshold() = 0;
  virtual void SetBufferedAmountLowThreshold(uint64_t threshold = 0) = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/maxPacketLifeTime

  virtual uint16_t MaxPacketLifeTime() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/maxRetransmits

  virtual uint16_t MaxRetransmits() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/negotiated

  virtual bool Negotiated() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/ordered

  virtual bool Ordered() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/protocol

  virtual std::string Protocol() = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/readyState

  virtual State ReadyState() = 0;

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/close

  virtual void Close() = 0;

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/send

  virtual void Send(const Let<ArrayBuffer>& data, bool binary = true) = 0;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/onbufferedamountlow

  Callback onbufferedamountlow;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/onclose

  Callback onclose;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/onerror

  ErrorCallback onerror;

  /// \sa
  /// https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/onmessage

  MessageCallback onmessage;

  //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel/onopen

  Callback onopen;

 protected:
  explicit RTCDataChannel();
  ~RTCDataChannel() override;
};

}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_DATA_CHANNEL_H_