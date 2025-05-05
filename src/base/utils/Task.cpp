//
// Created by shell on 2025/4/7.
//

#include "Task.h"
#include "base/utils/TaskGroup.h"

namespace bitcraft {
std::shared_ptr<Task> Task::Run(std::function<void()> block) {
  if (block == nullptr) {
    return nullptr;
  }

  auto task = std::shared_ptr<Task>(new Task(std::move(block)));
  if (!TaskGroup::GetInstance()->pushTask(task)) {
    task->execute();
  }
  return task;
}

Task::Task(std::function<void()> block) : block(std::move(block)) {

}

bool Task::executing() {
  std::lock_guard<std::mutex> autoLock(locker);
  return executing_;
}

bool Task::cancelled() {
  std::lock_guard<std::mutex> autoLock(locker);
  return cancelled_;
}

bool Task::finished() {
  std::lock_guard<std::mutex> autoLock(locker);
  return !executing_ && !cancelled_;
}

void Task::wait() {
  std::unique_lock<std::mutex> autoLock(locker);
  if (!executing_) {
    return;
  }
  if (removeTask()) {
    block();
    executing_ = false;
    condition.notify_all();
    return;
  }
  condition.wait(autoLock);
}

void Task::cancel() {
  std::unique_lock<std::mutex> autoLock(locker);
  if (!executing_) {
    return;
  }
  if (removeTask()) {
    executing_ = false;
    cancelled_ = true;
  }
}

bool Task::removeTask() {
  return TaskGroup::GetInstance()->removeTask(this);
}

void Task::execute() {
  block();
  std::lock_guard<std::mutex> autoLock(locker);
  executing_ = false;
  condition.notify_all();
}

}