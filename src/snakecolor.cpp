#include "snakecolor.h"
#include "config.h"
#include <chrono>
#include <iostream>

void SnakeColor::startTask() {
  /*
   * Attempt to set taskRunning_ to true.
   * If it was already true, the task is already running and we skip launching.
   * If it was false, we successfully mark it as running and proceed.
   */
  if (!taskRunning_.exchange(true)) {
    // Ensure previous thread is joined before launching a new one
    if (workerThread_.joinable()) {
      workerThread_.join(); // Join the previous thread if it was still active
    }

    // Reset stopRequested_ under lock
    {
      std::lock_guard<std::mutex> lock(stopMutex_);
      stopRequested_ = false;
    }

    workerThread_ = std::thread(&SnakeColor::task, this);
  } else {
    if constexpr (Config::ENABLE_SNAKECOLOR_DEBUG_MESSAGES) {
      std::cout << "Task already running. Skipping launch.\n";
    }
  }
}

void SnakeColor::task() {
  flagColor_.store(true); // Task begins
  if constexpr (Config::ENABLE_SNAKECOLOR_DEBUG_MESSAGES) {
    std::cout << "Task started: flagColor_ = true\n";
  }

  // Simulated work (n seconds) loop with cancellation check
  for (int i = 0; i < 30; ++i) {
    {
      std::lock_guard<std::mutex> lock(stopMutex_);
      if (stopRequested_)
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  flagColor_.store(false); // Task ends
  if constexpr (Config::ENABLE_SNAKECOLOR_DEBUG_MESSAGES) {
    std::cout << "Task completed: flagColor_ = false\n";
  }

  taskRunning_.store(false);
}

void SnakeColor::joinIfRunning() {
  // Request the task to stop under lock
  {
    std::lock_guard<std::mutex> lock(stopMutex_);
    stopRequested_ = true;
  }

  if (workerThread_.joinable()) {
    workerThread_.join();
  }
}

bool SnakeColor::isFlagColorSet() const { return flagColor_.load(); }

bool SnakeColor::isTaskRunning() const { return taskRunning_.load(); }
