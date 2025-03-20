//
// Created by shell on 2025/3/19.
//

#include "ScopedLock.h"

#include <utility>

namespace bitcraft {
ScopedLock::ScopedLock(std::shared_ptr<std::mutex> first, std::shared_ptr<std::mutex> second)
    : firstLocker(std::move(first)), secondLocker(std::move(second)) {
  if (firstLocker == nullptr) {
    return;
  }
  if (firstLocker == secondLocker) {
    secondLocker = nullptr;
  }

  if (secondLocker) {
    std::lock(*firstLocker, *secondLocker);
  } else {
    firstLocker->lock();
  }
}

ScopedLock::~ScopedLock() {
  if (firstLocker) {
    firstLocker->unlock();
  }
  if (secondLocker) {
    secondLocker->unlock();
  }
}
}