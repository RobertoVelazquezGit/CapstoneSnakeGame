#include "barrier.h"
#include "SDL.h"
#include <algorithm> // std::find
#include <utility>   // std::move

// ---------- Barrier common methods ----------
Barrier::Barrier(int grid_width, int grid_height, int num_points, int pos_y,
                 int pos_start_x)
    : gridwidth_(grid_width), gridheight_(grid_height),
      kNumberOf_points_(num_points), kPos_y_points_(pos_y),
      kPosStart_x_points_(pos_start_x) {}

const std::vector<SDL_Point> &Barrier::getBarrierPoints() const {
  return points_;
}

bool Barrier::contains(const SDL_Point &point) const {
  return std::any_of(points_.begin(), points_.end(), [&](const SDL_Point &p) {
    return p.x == point.x && p.y == point.y;
  });
}

bool Barrier::contains(int x, int y) const { return contains(SDL_Point{x, y}); }

// ---------- LineBarrier ----------
LineBarrier::LineBarrier(int grid_width, int grid_height)
    : Barrier(grid_width, grid_height, 8, grid_height / 4, grid_width / 4) {
  addBarrierPoints();
}

void LineBarrier::addBarrierPoints() {
  for (int i = 0; i < kNumberOf_points_; ++i) {
    SDL_Point point;
    point.x = i + kPosStart_x_points_;
    point.y = kPos_y_points_;
    points_.emplace_back(std::move(point));
  }
}

// ---------- SquareBarrier ----------
SquareBarrier::SquareBarrier(int grid_width, int grid_height)
    : Barrier(grid_width, grid_height, 9, grid_height * 3 / 4,
              grid_width * 3 / 4),
              kPointsPerRow_(3) {
  addBarrierPoints();
}

void SquareBarrier::addBarrierPoints() {

  // Parameter's checking: Only 2x2 or 3x3 square barrier allowed 
  int numberofrows;
  int numberofcolumns;
  if((kNumberOf_points_ == 4 && kPointsPerRow_ == 2) || (kNumberOf_points_ == 9 && kPointsPerRow_ == 3)){
    numberofrows = kNumberOf_points_ / kPointsPerRow_;
    numberofcolumns = kPointsPerRow_;
  }
  else{
    numberofrows = 2;
    numberofcolumns = 2;
  }

  // Build the square
  for (int row = 0; row < numberofrows; ++row) {    
    for(int column = 0; column < numberofcolumns; ++column){
      SDL_Point point;
      point.x = column + kPosStart_x_points_;
      point.y = row + kPos_y_points_;
      points_.emplace_back(std::move(point));  
    }
  }
}
