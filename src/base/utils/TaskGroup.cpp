//
// Created by shell on 2025/4/7.
//

#include "TaskGroup.h"
#include <cstdlib>

#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

namespace bitcraft {
static constexpr auto THREAD_TIMEOUT = std::chrono::seconds(10);

int GetCPUCores() {
  int cpuCores = 0;
#ifdef __APPLE__
  size_t len = sizeof(cpuCores);
  sysctlbyname("hw.physicalcpu", &cpuCores, &len, nullptr, 0);
#else
  cpuCores = static_cast<int>(std::thread::hardware_concurrency());
#endif
  if (cpuCores <= 0) {
    cpuCores = 8;
  }
  return cpuCores;
}

TaskGroup *TaskGroup::GetInstance() {
  static auto &taskGroup = *new TaskGroup();
  return &taskGroup;
}

void TaskGroup::RunLoop(bitcraft::TaskGroup *taskGroup) {
  while (true) {
    auto task = taskGroup->popTask();
    if (!task) {
      break;
    }
    task->execute();
  }
}

static void ReleaseThread(std::thread *thread) {
  if (thread->joinable()) {
    thread->join();
  }
  delete thread;
}

void OnAppExit() {
  TaskGroup::GetInstance()->exit();

}

TaskGroup::TaskGroup() {
  std::atexit(OnAppExit);
}

bool TaskGroup::checkThread() {
  static const int CPUCores = GetCPUCores();
  static const int MAXThreads = CPUCores > 16 ? 16 : CPUCores;
  while (!timeoutThreads.empty()) {
    auto threadID = timeoutThreads.back();
    timeoutThreads.pop_back();
    auto result = std::find_if(threads.begin(), threads.end(),
                               [=](std::thread *thread) { return thread->get_id() == threadID; });
    if (result != threads.end()) {
      ReleaseThread(*result);
      threads.erase(result);
    }
  }
  auto totalThreads = static_cast<int>(threads.size());
  if (activeThreads < totalThreads || totalThreads >= MAXThreads) {
    return true;
  }
  auto thread = new(std::nothrow) std::thread(&TaskGroup::RunLoop, this);
  if (thread) {
    activeThreads++;
    threads.push_back(thread);
  }
  return !threads.empty();
}

bool TaskGroup::pushTask(std::shared_ptr<Task> task) {
  std::lock_guard<std::mutex> autoLock(locker);
  if (exited || !checkThread()) {
    return false;
  }
  tasks.push_back(std::move(task));
  condition.notify_one();
  return true;
}

std::shared_ptr<Task> TaskGroup::popTask() {
  std::unique_lock<std::mutex> autoLock(locker);
  activeThreads--;
  while (!exited) {
    if (tasks.empty()) {
      auto status = condition.wait_for(autoLock, THREAD_TIMEOUT);
      if (exited || status == std::cv_status::timeout) {
        auto threadID = std::this_thread::get_id();
        timeoutThreads.push_back(threadID);
        return nullptr;
      }
    } else {
      auto task = tasks.front();
      tasks.pop_front();
      activeThreads++;
      return task;
    }
  }
  return nullptr;
}

bool TaskGroup::removeTask(Task *target) {
  std::lock_guard<std::mutex> autoLock(locker);
  auto position = std::find_if(tasks.begin(), tasks.end(),
                               [=](std::shared_ptr<Task> task) { return task.get() == target; });
  if (position == tasks.end()) {
    return false;
  }
  tasks.erase(position);
  return true;
}

void TaskGroup::exit() {
  locker.lock();
  exited = true;
  tasks.clear();
  condition.notify_all();
  locker.unlock();
  for (auto &thread : threads) {
    ReleaseThread(thread);
  }
  threads.clear();
}
}