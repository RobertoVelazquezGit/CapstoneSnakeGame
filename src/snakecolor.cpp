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
    stopRequested_.store(false); // Reset cancel flag when starting new trhead
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

  // Simulated work of 3 seconds
  for (int i = 0; i < 30 && !stopRequested_.load(); ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  flagColor_.store(false); // Task ends
  if constexpr (Config::ENABLE_SNAKECOLOR_DEBUG_MESSAGES) {
    std::cout << "Task completed: flagColor_ = false\n";
  }

  taskRunning_.store(false);
}

void SnakeColor::joinIfRunning() {
  if (taskRunning_.load()) {
    stopRequested_.store(true); // Signal to stop the thread
  }
  if (workerThread_.joinable()) {
    workerThread_.join();
  }
}

bool SnakeColor::isFlagColorSet() const { return flagColor_.load(); }

bool SnakeColor::isTaskRunning() const { return taskRunning_.load(); }
