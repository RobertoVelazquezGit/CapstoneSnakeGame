
#ifndef BARRIER_H
#define BARRIER_H

#include "SDL.h"
#include <vector>

class Barrier {
public:
  Barrier(int grid_width, int grid_height)
      : gridwidth_(grid_width), gridheight_(grid_height), kNumberOf_points_(8U),
        kPos_y_points_(grid_height / 4U), kPosStart_x_points_(grid_width / 4U) {
    addBarrierPoints();
  }
  const std::vector<SDL_Point> &getBarrierPoints() const;
  bool contains(const SDL_Point &point) const;
  bool contains(int x, int y) const;

private:
  std::vector<SDL_Point> points_;
  int gridwidth_;
  int gridheight_;
  const int kNumberOf_points_;
  const int kPos_y_points_;
  const int kPosStart_x_points_;

  void addBarrierPoints();
};
#endif