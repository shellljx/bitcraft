//
// Created by shell on 2025/4/7.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_UTILS_TASK_H_
#define BITCRAFT_LINUX_SRC_BASE_UTILS_TASK_H_

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>

namespace bitcraft {
class TaskGroup;

class Task {
 public:
  static std::shared_ptr<Task> Run(std::function<void()> block);

  bool executing();
  bool cancelled();
  bool finished();
  void cancel();
  void wait();

 private:
  std::mutex locker = {};
  std::condition_variable condition = {};
  bool executing_ = true;
  bool cancelled_ = false;
  std::function<void()> block = nullptr;

  explicit Task(std::function<void()> block);
  bool removeTask();
  void execute();

  friend class TaskGroup;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_UTILS_TASK_H_
