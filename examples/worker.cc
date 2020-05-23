#include <stdio.h>
#include <string>
#include <utility>

#include "rc_crtc.h"

using namespace crtc;

static int total = 0, requested = 1;

int main() {
#if defined(_DEBUG) && defined(_MSC_VER) && defined(WIN32)
  int Flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
  Flag |= _CRTDBG_LEAK_CHECK_DF;
  _CrtSetDbgFlag(Flag);
  //_CrtSetBreakAlloc(2656);
#endif
  Module::Init();
  
  printf("Creating Workers...\n");
  std::vector<Let<Worker>> workers;
  for (int index = 0; index < requested; index++) {
    Let<Worker> worker =  Worker::New([index]() {
      SetTimeout([=]() {
        if (!Worker::This().IsEmpty()) {
          printf("I'M WORKER[%d]!\n", index);
          total++;
        } else {
          printf("I'M NOT WORKER[%d]!\n", index);
        }
      }, 6000);
    });
  }

  printf("All Workers are now created. Idling for 30 seconds...\n");

  Module::DispatchEvents(true);
  Module::Dispose();

  if (total != requested) {
    printf("Test Failed: current count: %d, requested count: %d\n", total, requested);
  } else {
    printf("All %d workers created!\n", total);
  }

  return 0;
};