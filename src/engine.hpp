#pragma once

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "text.hpp"
#include "graphic.hpp"
#include "data.hpp"

class Engine {
 public:
  Engine();
  ~Engine();
  bool Run();

 private:
  std::shared_ptr<Graphic> graphic_;
  std::unique_ptr<Text> text_;
  std::unique_ptr<Data> data_;
};
