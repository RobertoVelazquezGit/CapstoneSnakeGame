#include "snakecolor.h"
#include <chrono>
#include <iostream>

void SnakeColor::startTask() {
  /*
   * Attempt to set taskRunning to true.
   * If it was already true, the task is already running and we skip launching.
   * If it was false, we successfully mark it as running and proceed.
   */
  if (!taskRunning.exchange(true)) {
    // Ensure previous thread is joined before launching a new one
    if (workerThread_.joinable()) {
      workerThread_.join(); // Join the previous thread if it was still active
    }
    workerThread_ = std::thread(&SnakeColor::task, this);
  } else {
    std::cout << "Task already running. Skipping launch.\n";
  }
}

void SnakeColor::task() {
  flagColor.store(true); // Task begins
  std::cout << "Task started: flagColor = true\n";

  std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulated work

  flagColor.store(false); // Task ends
  std::cout << "Task completed: flagColor = false\n";

  taskRunning.store(false);
}

void SnakeColor::joinIfRunning() {
  if (workerThread_.joinable()) {
    workerThread_.join();
  }
}

bool SnakeColor::isFlagColorSet() const { return flagColor.load(); }

bool SnakeColor::isTaskRunning() const { return taskRunning.load(); }
