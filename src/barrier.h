
#ifndef BARRIER_H
#define BARRIER_H

#include "SDL.h"
#include <vector>

class Barrier {
public:
  Barrier(int grid_width, int grid_height, int num_points, int pos_y,
          int pos_start_x);

  const std::vector<SDL_Point> &getBarrierPoints() const;
  bool contains(const SDL_Point &point) const;
  bool contains(int x, int y) const;

protected:
  std::vector<SDL_Point> points_;
  int gridwidth_;
  int gridheight_;
  const int kNumberOf_points_;
  const int kPos_y_points_;
  const int kPosStart_x_points_;

  virtual void addBarrierPoints() = 0; // abstract method
};

class LineBarrier : public Barrier {
public:
  LineBarrier(int grid_width, int grid_height);

private:
  void addBarrierPoints() override;
};

class SquareBarrier : public Barrier {
public:
  SquareBarrier(int grid_width, int grid_height);

private:
  void addBarrierPoints() override;
  const int kPointsPerRow_;
};

#endif