# CPPND: Capstone Snake Game Example

The starter repo for the Capstone project is in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives the student a chance to integrate what the the student has learned throughout this program. This project will become an important part of sutdent's portfolio to share with current and future colleagues and employers.

In this project, the student can build his own C++ application or extend this Snake game, following the principles the student has learned throughout this Nanodegree Program. This project will demonstrate that the student can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions (1)

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Basic Build Instructions (2)

1. On ${CMAKE_SOURCE_DIR} folder (where the CMakeLists.txt resides)
2. Clean everything: `make clean`
3. Build: `make build`
4. Run it: Get into build folder with `cd build`, the execute `./SnakeGame`

## Basic Debug Instructions 

1. Visual Studio Code `Run/Start Debugging` or F5. launch.json is applied, which launches my_make_debug task on tasks.json.


## CC Attribution-ShareAlike 4.0 International

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg


## Features added to the project

1. Barrier abstract base class (barrier.cpp, barrier.h). A LineBarrier and a SquareBarrier classes are derived from Barrier and rendered, having a linear barrier and a square barrier. If the snake hits any of the two barriers, the game ends.
2. Rule of Five on Renderer class (renderer.cpp, renderer.h). Use of unique pointers with SDL2 custom deleters, wich are automatically called when the instance of Renderer goes out of scope.
3. SnakeColor class to change the snake's color when eats food. This is accomplished launching a std::thread worker thread and taking care of properly joining it. While the worker thread is running, the snake is rendered in a different color. Atomic boolean flags are used to keep status of the worker thread and to signal the worker thread to finish.
4. ScoreRecord class saves and recovers from a scorerecord.txt file the highest record and the latest record. If the file does not exists it is created on ${CMAKE_SOURCE_DIR} folder.
5. config.h file contains the Config namespace. Config::ENABLE_SNAKECOLOR_DEBUG_MESSAGES member enbales/disables code to print out debug messages of SnakeColor class making use of constexpr.


## Udacity's criteria accomplishment

1. Loop, Functions, I/O
1.1 The project demonstrates an understanding of C++ functions and control structures.
 `void SquareBarrier::addBarrierPoints()` on barrier.cpp line 48.
1.2 The project reads data from a file and process the data, or the program writes data to a file.
 `coreRecord::ScoreRecord()` on scorerecord.cpp line 12.
1.4 The project uses data structures and immutable variables.
 `kNumberOf_points_, kPos_y_points_, kPosStart_x_points_` from Barrier class on barrier.cpp line 21.

2. Object Oriented Programming 
2.1 One or more classes are added to the project with appropriate access specifiers for class members.
 Added Barrier class on barrier.h and cpp.
 Added SnakeColor class on snakecolor.h and cpp.
 Added ScoreRecord class on scorerecord.h and cpp.
2.2 Class constructors utilize member initialization lists.
 Barrier base class constructor on barrier.cpp line 9.
 LineBarrier derived class constructor on barrier.cpp line 26.
 SquareBarrier derived class constructor on barrier.cpp line 41.
2.4 Overloaded functions allow the same function to operate on different parameters.
 `bool Barrier::contains(const SDL_Point &point) const` and bool Barrier::contains(int x, int y) const on barrier.cpp lines 17 and 23.
2.5 Classes follow an appropriate inheritance hierarchy with virtual and override functions.
 `virtual void addBarrierPoints() = 0` abstract method on abstract base class Barrier, barrier.h line 25.
 `void addBarrierPoints() override` on derived class LineBarrier, barrier.h line 33.
 `void addBarrierPoints() override` on derived class SquareBarrier, barrier.h line 41.

3. Memory Management
3.1 The project makes use of references in function declarations.
 `renderer.Render(snake, food, linebarrier_, squarebarrier_, snakecolor_);` on game.cpp line 31. References to `linebarrier_`, `squarebarrier_` and `snakecolor_` instances composing the game instance are passed to `Renderer::Render` method.
3.2 The project uses destructors appropriately.
 `Renderer::~Renderer()` destructor from Renderer class, on renderer.cpp line 39.
3.4 The project follows the Rule of 5.
 Render (renderer.h and cpp) class follows rule of five. Renderer.h line 13.
 Destructor calls automatically the SDL2 custom deleters `SDL_DestroyWindow` and `SDL_DestroyRenderer`. The custom deleters are associated to the unique pointers when these are initialized in the constructor. Example `sdl_window(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN),     SDL_DestroyWindow)` on renderer.cpp `Renderer::Renderer(const std::size_t screen_width` parametrized constructor.
3.5 The project uses move semantics to move data instead of copying it, where possible.
 In in void LineBarrier::addBarrierPoints() method `points_.emplace_back(std::move(point));` on barrier.cpp line 36.
 In movement constructor of Renderer class, on `sdl_window(std::move(other.sdl_window))` renderer.cpp line 112.
3.6 The project uses smart pointers instead of raw pointers.
 `sdl_window` unique_ptr, renderer.h line 49.
 `sdl_renderer` unique_ptr, renderer.h line 53.

4. Concurrency
4.1 The project uses multithreading.
 `std::thread workerThread_`in snakecolor.h line 23, launched from `void SnakeColor::startTask()` with the funcion `void SnakeColor::task()`. the std::thread is launched when the snake eats food `snakecolor_.startTask();` in `void Game::Update()` on game.cpp line 99.
4.3 A mutex or lock is used in the project.
 ToDo

 
 



