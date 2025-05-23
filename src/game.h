#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "barrier.h"
#include "snakecolor.h"
#include "scorerecord.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
 /*
  * The barriers belongs to the game
  * Barriers are initialized before snake because snake is initialized with the barriers
  */
  LineBarrier linebarrier_;
  SquareBarrier squarebarrier_;
  Snake snake;  
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  
  SnakeColor snakecolor_;

  ScoreRecord scorerecord_;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif