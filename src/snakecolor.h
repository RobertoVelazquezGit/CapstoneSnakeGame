#ifndef SNAKECOLOR_H
#define SNAKECOLOR_H

#include <atomic>
#include <thread>

class SnakeColor {
public:
    SnakeColor() = default;

    void startTask();             // Launches task if not already running
    void joinIfRunning();         // Joins the thread if joinable

    bool isFlagColorSet() const;
    bool isTaskRunning() const;

private:
    void task();                  // Background task logic

    std::atomic<bool> flagColor{false};
    std::atomic<bool> taskRunning{false};
    std::thread workerThread_;
};

#endif // SNAKECOLOR_H


