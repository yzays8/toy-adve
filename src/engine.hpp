#pragma once

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "text.hpp"
#include "graphic.hpp"

class Engine {
 public:
  Engine();
  ~Engine();
  void Run();

 private:
  std::shared_ptr<Graphic> graphic_;
  std::unique_ptr<Text> text_;
};
