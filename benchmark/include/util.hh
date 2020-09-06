#pragma once

#include <chrono>
#include <thread>

#include "atomic_wrapper.h"

namespace ccbench {

extern void chkArg();

inline bool isReady(const std::vector<char> &readys) {
  for (const char &b : readys) {
    if (!loadAcquire(b)) return false;
  }
  return true;
}

inline void sleepMs(std::size_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

extern void displayParameter();

extern void waitForReady(const std::vector<char> &readys);

}
