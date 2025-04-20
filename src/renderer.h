#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "barrier.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer {
public:
  // Rule of five
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  Renderer(const Renderer& source);
  Renderer& operator = (const Renderer& source);
  Renderer(Renderer &&other);
  Renderer& operator = (Renderer&& other);
  
  
  void Render(Snake const snake, SDL_Point const &food,
              LineBarrier const &linebarrier,
              SquareBarrier const &squarebarrier);
  void UpdateWindowTitle(int score, int fps);

private:
/*
* The order in which class members are initialized follows the order in which they are declared,
* not the order in which you initialize them in the constructor.
*
* The order of destruction of members of a class does follow the order in which they are declared
* in the class, not the order in which they are initialized in the constructor.
*/
  using SdlWindowPtr =
      std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  SdlWindowPtr sdl_window;

  using SdlRendererPtr =
      std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
  SdlRendererPtr sdl_renderer;

  /*
  * No const because assigned in assignemnt operators
  */
  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif