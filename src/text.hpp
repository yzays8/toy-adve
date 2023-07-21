#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL_ttf.h>

#include "graphic.hpp"

const std::string kFontPath{"../assets/fonts/SourceHanSansHW-VF.ttf"};

class Text {
 public:
  Text(std::shared_ptr<Graphic> image);
  ~Text();
  void Initialize();
  void RenderText(const std::string text);
  SDL_Surface GetNameSurface(const std::string name, SDL_Color color);

 private:
  std::shared_ptr<Graphic> graphic_;
  TTF_Font* font_;
  SDL_Color color_;
};
