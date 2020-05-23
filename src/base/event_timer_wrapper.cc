#include "event_timer_wrapper.h"

#if defined(CRTC_OS_WIN)
#include <windows.h>
#include "event_timer_win.h"
#elif defined(CRTC_OS_OSX) && !defined(CRTC_OS_IOS)
#include <ApplicationServices/ApplicationServices.h>
#include <pthread.h>
#include "event_timer_posix.h"
#else
#include <pthread.h>
#include "event_timer_posix.h"
#endif
