//
// Created by shell on 2025/4/7.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_UTILS_TASKGROUP_H_
#define BITCRAFT_LINUX_SRC_BASE_UTILS_TASKGROUP_H_

#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include "base/utils/Task.h"

namespace bitcraft {
class TaskGroup {
 private:
  std::mutex locker = {};
  std::condition_variable condition = {};
  int activeThreads = 0;
  bool exited = false;
  std::list<std::shared_ptr<Task>> tasks = {};
  std::vector<std::thread *> threads = {};
  std::vector<std::thread::id> timeoutThreads = {};

  static TaskGroup *GetInstance();
  static void RunLoop(TaskGroup *taskGroup);

  TaskGroup();
  bool checkThread();
  bool pushTask(std::shared_ptr<Task> task);
  std::shared_ptr<Task> popTask();
  bool removeTask(Task *target);
  void exit();

  friend class Task;
  friend void OnAppExit();
};
}
#endif //BITCRAFT_LINUX_SRC_BASE_UTILS_TASKGROUP_H_
