#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "barrier.h"
#include "snake.h"
#include <vector>
#include <memory>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food,
              LineBarrier const &linebarrier,
              SquareBarrier const &squarebarrier);
  void UpdateWindowTitle(int score, int fps);

private:
  using SdlWindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  SdlWindowPtr sdl_window;

  using SdlRendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
  SdlRendererPtr sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif