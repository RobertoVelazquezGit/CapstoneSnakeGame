#ifndef SNAKECOLOR_H
#define SNAKECOLOR_H

#include <memory>
#include <atomic>
#include <thread>

// Shared state between objects and threads
struct StateSnakeColor {
    std::atomic<bool> flagDifferentColor{false};
    std::atomic<bool> taskLaunched{false}; // Ensures task is only launched once
};

// Class that manages a background task
class SnakeColor {
public:
    explicit SnakeColor(std::shared_ptr<StateSnakeColor> stateSnakeColor);

    // Launches a background task if not already launched
    std::thread launchTask();

private:
    void task(std::shared_ptr<StateSnakeColor> stateSnakeColor);

    std::shared_ptr<StateSnakeColor> stateSnakeColor_;
};

#endif // SNAKECOLOR_H


