//
// Created by shell on 2025/3/19.
//

#ifndef BITCRAFT_SRC_BASE_UTILS_SCOPEDLOCK_H_
#define BITCRAFT_SRC_BASE_UTILS_SCOPEDLOCK_H_

#include <memory>
#include <mutex>

namespace bitcraft {
class ScopedLock {
 public:
  ScopedLock(std::shared_ptr<std::mutex> first, std::shared_ptr<std::mutex> second);

  ~ScopedLock();

 private:
  std::shared_ptr<std::mutex> firstLocker = nullptr;
  std::shared_ptr<std::mutex> secondLocker = nullptr;
};
}

#endif //BITCRAFT_SRC_BASE_UTILS_SCOPEDLOCK_H_
