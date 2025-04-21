#include "snakecolor.h"
#include <chrono>
#include <iostream>

SnakeColor::SnakeColor(std::shared_ptr<StateSnakeColor> stateSnakeColor) : stateSnakeColor_(stateSnakeColor) {}

std::thread SnakeColor::launchTask() {
    if (!stateSnakeColor_->taskLaunched.load()) {
        stateSnakeColor_->taskLaunched.store(true);
        return std::thread([this, stateCopy = stateSnakeColor_]() {
            task(stateCopy);
        });
    }
    return std::thread(); // Return empty thread if already launched
}

void SnakeColor::task(std::shared_ptr<StateSnakeColor> stateSnakeColor) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    stateSnakeColor->flagDifferentColor.store(true);
    std::cout << "Task completed: flag = true\n";
}

