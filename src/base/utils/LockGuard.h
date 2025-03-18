//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_SRC_BASE_UTILS_LOCKGUARD_H_
#define BITCRAFT_SRC_BASE_UTILS_LOCKGUARD_H_

#include <memory>
#include <mutex>

namespace bitcraft {

class LockGuard {
 public:
  explicit LockGuard(std::shared_ptr<std::mutex> locker) : mutex(std::move(locker)) {
    if (mutex) {
      mutex->lock();
    }
  }

  ~LockGuard() {
    if (mutex) {
      mutex->unlock();
    }
  }

 private:
  std::shared_ptr<std::mutex> mutex;
};
}
#endif //BITCRAFT_SRC_BASE_UTILS_LOCKGUARD_H_
