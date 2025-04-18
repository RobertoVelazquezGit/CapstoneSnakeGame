#include "barrier.h"
#include "SDL.h"
#include <algorithm> // std::find
#include <utility>   // std::move

void Barrier::addBarrierPoints() {
  for (int i = 0U; i < kNumberOf_points_; i++) {
    SDL_Point point;
    point.x = i + kPosStart_x_points_;
    point.y = kPos_y_points_;
    points_.emplace_back(std::move(point));
  }
}

const std::vector<SDL_Point> &Barrier::getBarrierPoints() const {
  return points_;
}

// overloaded contains with SDL_Point
bool Barrier::contains(const SDL_Point &point) const {
  return std::find_if(points_.begin(), points_.end(),
                      [&point](const SDL_Point &p) {
                        return p.x == point.x && p.y == point.y;
                      }) != points_.end();
}

// overloaded contains with x and y
bool Barrier::contains(int x, int y) const {
  return std::find_if(points_.begin(), points_.end(),
                      [x, y](const SDL_Point &p) {
                        return p.x == x && p.y == y;
                      }) != points_.end();
}
