/*
#
# Copyright 2020, rc inc
# author: hhool
# rc_peer_connection.h
# 2020-05-22
#
*/

#ifndef _RC_CPLUS_INCLUDE_RC_PEER_CONNECTION_H_
#define _RC_CPLUS_INCLUDE_RC_PEER_CONNECTION_H_

#include "rc_common.h"
#include "rc_let.h"
#include "rc_audio.h"
#include "rc_video.h"
#include "rc_data_channel.h"
#include "rc_media_stream.h"

namespace crtc {

//TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection

class CRTC_EXPORT RTCPeerConnection : virtual public Reference {
    CRTC_PRIVATE(RTCPeerConnection);

  public:
    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/createDataChannel#RTCDataChannelInit_dictionary
    
    typedef struct RTCDataChannelInit {
      RTCDataChannelInit() :
        id(-1),
        maxPacketLifeTime(-1),
        maxRetransmits(-1),
        ordered(true),
        negotiated(false)
      { }

      int id;
      int maxPacketLifeTime;
      int maxRetransmits;
      bool ordered;
      bool negotiated;
      std::string protocol;
    } RTCDataChannelInit;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCSessionDescription

    typedef struct {
      enum RTCSdpType {
        kAnswer,
        kOffer,
        kPranswer,
        kRollback,
      };

      RTCSdpType type;
      std::string sdp;
    } RTCSessionDescription;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/signalingState

    enum RTCSignalingState {
      kStable,
      kHaveLocalOffer,
      kHaveLocalPrAnswer,
      kHaveRemoteOffer,
      kHaveRemotePrAnswer,
      kSignalingClosed,
    };

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/iceGatheringState

    enum RTCIceGatheringState {
      kNewGathering,
      kGathering,
      kComplete
    };

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/iceConnectionState

    enum RTCIceConnectionState {
      kNew,
      kChecking,
      kConnected,
      kCompleted,
      kFailed,
      kDisconnected,
      kClosed,
    };

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCConfiguration#RTCBundlePolicy_enum

    enum RTCBundlePolicy {
      kBalanced,
      kMaxBundle,
      kMaxCompat
    };

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCConfiguration#RTCIceTransportPolicy_enum

    enum RTCIceTransportPolicy {
      kRelay,
      kPublic,
      kAll
    };

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCConfiguration#RTCRtcpMuxPolicy_enum

    enum RTCRtcpMuxPolicy {
      kNegotiate,
      kRequire,
    };

    // \sa https://developer.mozilla.org/en/docs/Web/API/RTCIceCandidate

    typedef struct {
      std::string candidate;
      std::string sdpMid;
      uint32_t sdpMLineIndex;
    } RTCIceCandidate;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCIceServer

    typedef struct {
      std::string credential;
      std::string credentialType;
      std::string username;
      std::vector<std::string> urls;
    } RTCIceServer;

    typedef std::vector<RTCIceServer> RTCIceServers;

    static RTCIceServers defaultIceServers;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCConfiguration

    typedef struct CRTC_EXPORT RTCConfiguration {
      explicit RTCConfiguration();
      ~RTCConfiguration();

      uint16_t iceCandidatePoolSize;
      RTCBundlePolicy bundlePolicy;       
      RTCIceServers iceServers;
      RTCIceTransportPolicy iceTransportPolicy;
      RTCRtcpMuxPolicy rtcpMuxPolicy;
    } RTCConfiguration;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/createOffer#RTCOfferOptions_dictionary
    //TODO(hhool):https://w3c.github.io/webrtc-pc/#idl-def-rtcofferansweroptions

    typedef struct {
      bool voiceActivityDetection;
    } RTCOfferAnswerOptions;

    //TODO(hhool):https://w3c.github.io/webrtc-pc/#idl-def-rtcofferoptions

    typedef struct : RTCOfferAnswerOptions {
      bool iceRestart;
    } RTCOfferOptions;

    //TODO(hhool):https://w3c.github.io/webrtc-pc/#idl-def-rtcansweroptions

    typedef struct : RTCOfferAnswerOptions {
    } RTCAnswerOptions;

    typedef Functor<void(const Let<MediaStream> &stream)> StreamCallback;
    typedef Functor<void(const Let<RTCDataChannel> &dataChannel)> DataChannelCallback;
    typedef Functor<void(const RTCIceCandidate &candidate)> IceCandidateCallback;

    static Let<RTCPeerConnection> New(const RTCConfiguration &config = RTCConfiguration());

    virtual Let<RTCDataChannel> CreateDataChannel(const std::string &label, const RTCDataChannelInit &options = RTCDataChannelInit()) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/addIceCandidate

    virtual Let<Promise<void>> AddIceCandidate(const RTCIceCandidate &candidate) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/addStream

    virtual void AddStream(const Let<MediaStream> &stream) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/createAnswer

    virtual Let<Promise<RTCSessionDescription>> CreateAnswer(const RTCAnswerOptions &options = RTCAnswerOptions()) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/createOffer

    virtual Let<Promise<RTCSessionDescription>> CreateOffer(const RTCOfferOptions &options = RTCOfferOptions()) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/getLocalStreams

    virtual MediaStreams GetLocalStreams() = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/getRemoteStreams

    virtual MediaStreams GetRemoteStreams() = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/removeStream

    virtual void RemoveStream(const Let<MediaStream> &stream) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/setConfiguration

    virtual void SetConfiguration(const RTCConfiguration &config) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/setLocalDescription

    virtual Let<Promise<void>> SetLocalDescription(const RTCSessionDescription &sdp) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/setRemoteDescription

    virtual Let<Promise<void>> SetRemoteDescription(const RTCSessionDescription &sdp) = 0;

    //TODO(hhool):https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection/close

    virtual void Close() = 0;

    virtual RTCSessionDescription CurrentLocalDescription() = 0;
    virtual RTCSessionDescription CurrentRemoteDescription() = 0;
    virtual RTCSessionDescription LocalDescription() = 0;
    virtual RTCSessionDescription PendingLocalDescription() = 0;
    virtual RTCSessionDescription PendingRemoteDescription() = 0;
    virtual RTCSessionDescription RemoteDescription() = 0; 

    virtual RTCIceConnectionState IceConnectionState() = 0;
    virtual RTCIceGatheringState IceGatheringState() = 0;
    virtual RTCSignalingState SignalingState() = 0;

    Callback onnegotiationneeded;
    Callback onsignalingstatechange;
    Callback onicegatheringstatechange;
    Callback oniceconnectionstatechange;
    Callback onicecandidatesremoved;
    StreamCallback onaddstream;
    StreamCallback onremovestream;
    DataChannelCallback ondatachannel;
    IceCandidateCallback onicecandidate;

  protected:
    explicit RTCPeerConnection();
    ~RTCPeerConnection() override;
};
}  // namespace crtc
#endif  //_RC_CPLUS_INCLUDE_RC_PEER_CONNECTION_H_