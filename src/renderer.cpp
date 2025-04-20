#include "renderer.h"
#include "barrier.h"
#include <iostream>
#include <memory>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height),
      sdl_window(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN),
                 SDL_DestroyWindow),
      sdl_renderer(
          SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED),
          SDL_DestroyRenderer) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Check sdl_window smart pointer
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Check sdl_renderer smart pointer
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

// Destructor
Renderer::~Renderer() { SDL_Quit(); }

// Copy constructor
Renderer::Renderer(const Renderer &source)
    : screen_width(source.screen_width), screen_height(source.screen_height),
      grid_width(source.grid_width), grid_height(source.grid_height),
      sdl_window(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN),
                 SDL_DestroyWindow),
      sdl_renderer(
          SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED),
          SDL_DestroyRenderer) {
  // Check sdl_window smart pointer
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Check sdl_renderer smart pointer
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

// Copy assignment operator
Renderer &Renderer::operator=(const Renderer &source) {
  if (&source == this) {
    return *this;
  } else {
    this->screen_width = source.screen_width;
    this->screen_height = source.screen_height;
    this->grid_width = source.grid_width;
    this->grid_height = source.grid_height;

    /*
     * unique pointer sdl_window
     */
    auto raw_window = SDL_CreateWindow(
        "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        source.screen_width, source.screen_height, SDL_WINDOW_SHOWN);
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> temp_window(
        raw_window, SDL_DestroyWindow);
    this->sdl_window = std::move(temp_window);
    if (nullptr == this->sdl_window) {
      std::cerr << "Window could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    /*
     * unique pointer sdl_renderer
     */
    auto raw_renderer = SDL_CreateRenderer(this->sdl_window.get(), -1,
                                           SDL_RENDERER_ACCELERATED);
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> temp_renderer(
        raw_renderer, SDL_DestroyRenderer);
    this->sdl_renderer = std::move(temp_renderer);
    if (nullptr == this->sdl_renderer) {
      std::cerr << "Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    return *this;
  }
}

// Movement constructor
Renderer::Renderer(Renderer &&other)
    : screen_width(other.screen_width),
      screen_height(other.screen_height),
      grid_width(other.grid_width),
      grid_height(other.grid_height),
      sdl_window(std::move(other.sdl_window)),
      sdl_renderer(std::move(other.sdl_renderer)) {}

// Movement assignment operator      
Renderer& Renderer::operator = (Renderer &&other){
  if(&other == this){
    return *this;
  }    
  else{
    this->screen_width = other.screen_width;
    this->screen_height = other.screen_height;
    this->grid_width = other.grid_width;
    this->grid_height = other.grid_height;
    sdl_window = std::move(other.sdl_window);
    sdl_renderer = std::move(other.sdl_renderer);
    return *this;
  }
}

void Renderer::Render(Snake const snake, SDL_Point const &food,
                      LineBarrier const &linebarrier,
                      SquareBarrier const &squarebarrier) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Render line barrier
  SDL_SetRenderDrawColor(sdl_renderer.get(), 255, 0, 0, 255);
  for (const SDL_Point &barrierPoint : linebarrier.getBarrierPoints()) {
    block.x = barrierPoint.x * block.w;
    block.y = barrierPoint.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render square barrier
  SDL_SetRenderDrawColor(sdl_renderer.get(), 255, 0, 0, 255);
  for (const SDL_Point &barrierPoint : squarebarrier.getBarrierPoints()) {
    block.x = barrierPoint.x * block.w;
    block.y = barrierPoint.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
