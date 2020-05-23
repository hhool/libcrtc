
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

/**
\mainpage WebRTC C++ library
WebRTC (Web Real-Time Communication) is a collection of communications protocols and application programming interfaces that enable real-time communication over peer-to-peer connections. 
This allows web browsers to not only request resources from backend servers, but also real-time information from browsers of other users.

This enables applications such as video conferencing, file transfer, chat, or desktop sharing without the need of either internal or external plugins.

WebRTC is being standardized by the World Wide Web Consortium (W3C) and the Internet Engineering Task Force (IETF). 
The reference implementation is released as free software under the terms of a BSD license. 

WebRTC uses Real-Time Protocol to transfer audio and video.
\sa https://webrtc.org/
*/

/** @file */

#ifndef INCLUDE_CRTC_H_
#define INCLUDE_CRTC_H_

#include <utility>
#include <memory>
#include <vector>
#include <string>

#include "rc_common.h"
#include "rc_reference.h"
#include "rc_let.h"
#include "rc_functor.h"
#include "rc_atomic.h"
#include "rc_time.h"
#include "rc_worker.h"
#include "rc_real_time_clock.h"
#include "rc_async.h"
#include "rc_event.h"
#include "rc_error.h"
#include "rc_promise.h"
#include "rc_array_buffer.h"
#include "rc_image_buffer.h"
#include "rc_media_stream.h"
#include "rc_audio.h"
#include "rc_video.h"
#include "rc_data_channel.h"
#include "rc_peer_connection.h"

namespace crtc {

class CRTC_EXPORT Module {
    CRTC_STATIC(Module);
  public:
    static void Init();
    static bool DispatchEvents(bool kForever = false);
    static void Dispose();
};

}; // namespace crtc

#endif // INCLUDE_CRTC_H_