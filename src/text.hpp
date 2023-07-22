#pragma once

#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL_ttf.h>

#include "graphic.hpp"

class Text {
 public:
  Text(std::shared_ptr<Graphic> image, std::string font_path);
  ~Text();
  void Initialize(std::string font_path);
  void RenderText(const std::vector<std::string> texts);
  SDL_Surface GetNameSurface(const std::string name, SDL_Color color);

 private:
  std::shared_ptr<Graphic> graphic_;
  TTF_Font* font_;
  SDL_Color color_;
};
