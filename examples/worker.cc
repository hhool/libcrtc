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
  //_CrtSetBreakAlloc(154);
#endif
  Module::Init();

  printf("Creating Workers...\n");
  Let<Worker> worker =  Worker::New([&]() {
    SetTimeout(
        [=]() {
          if (!Worker::This().IsEmpty()) {
            printf("I'M WORKER!\n");
            total++;
          } else {
            printf("I'M NOT WORKER!\n");
          }
        },
        6000);
  });

  printf("All Workers are now created. Idling for 10 seconds...\n");

  Module::DispatchEvents(true);
  worker.Dispose();
  Module::Dispose();

  if (total != requested) {
    printf("Test Failed: current count: %d, requested count: %d\n", total,
           requested);
  } else {
    printf("All %d workers created!\n", total);
  }

  return 0;
};