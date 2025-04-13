#include <utility>  // std::move
#include "SDL.h"
#include "barrier.h"

void Barrier::addBarrierPoints() {
  for (int i = 0U; i < kNumberOf_points_; i++) {
    SDL_Point point;
    point.x = i + kPosStart_x_points_;
    point.y = kPos_y_points_;
    points_.emplace_back(std::move(point));
  }
}