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

#include "module.h"
#include "async.h"
#include "rc_crtc.h"
#include "rtcpeerconnection.h"
//#include "videosource.h"

#include "rtc_base/event_tracer.h"
#include "rtc_base/logging.h"
#include "rtc_base/ssl_adapter.h"
#include "rtc_base/thread.h"

#ifdef CRTC_OS_OSX
#include "rtc_base/cocoa_threading.h"
#endif

#ifdef CRTC_OS_WIN
#include "rtc_base/win32_socket_init.h"
#include "rtc_base/win32_socket_server.h"
namespace crtc {
std::unique_ptr<rtc::WinsockInitializer> g_winsock_init_;
std::unique_ptr<rtc::Thread> g_auto_thread_;
}
#endif

using namespace crtc;

volatile int ModuleInternal::pending_events = 0;
void Module::Init() {
#ifdef CRTC_OS_OSX
  rtc::InitCocoaMultiThreading();
#endif

#ifdef CRTC_OS_WIN
  crtc::g_winsock_init_.reset(new rtc::WinsockInitializer());
#endif

  crtc::g_auto_thread_.reset(rtc::Thread::CreateWithSocketServer().release());
  rtc::ThreadManager::Instance()->SetCurrentThread(crtc::g_auto_thread_.get());
  //rtc::ThreadManager::Instance()->WrapCurrentThread();
  // webrtc::Trace::CreateTrace();
  // rtc::LogMessage::LogToDebug(rtc::LS_ERROR);

  rtc::InitializeSSL();

  AsyncInternal::Init();
  RTCPeerConnectionInternal::Init();
}

void Module::Dispose() {
  RTCPeerConnectionInternal::Dispose();
  AsyncInternal::Dispose();
  rtc::CleanupSSL();
  rtc::ThreadManager::Instance()->SetCurrentThread(nullptr);
  crtc::g_auto_thread_.reset();
#ifdef CRTC_OS_WIN
  crtc::g_winsock_init_.reset();
#endif
}

bool Module::DispatchEvents(bool kForever) {
  bool result = false;

  do {
    result =
        (rtc::AtomicOps::AcquireLoad(&ModuleInternal::pending_events) > 0 &&
         rtc::Thread::Current()->ProcessMessages(kForever ? 1000 : 1));
  } while (kForever && result);

  return result;
}
