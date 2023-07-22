#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "text.hpp"
#include "graphic.hpp"
#include "data.hpp"

class Engine {
 public:
  Engine(std::string game);
  ~Engine();
  bool Run();

 private:
  std::unique_ptr<Data> data_;
  std::shared_ptr<Graphic> graphic_;
  std::unique_ptr<Text> text_;
};
