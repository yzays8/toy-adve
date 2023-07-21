#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphic.hpp"

Graphic::Graphic()
    : bg_rect_{0, 0, kWindowWidth, kWindowHeight},
      textbox_rect_{80, kWindowHeight - 200, kWindowWidth - 160, 200},
      namebox_rect_{150, kWindowHeight - 245, 300, 40},
      name_rect_{},
      bg_texture_{nullptr},
      name_texture_{nullptr} {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cerr << "IMG_Init Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
}

void Graphic::InitializeWindow(std::string window_title) {
  if (SDL_CreateWindowAndRenderer(kWindowWidth, kWindowHeight, 0, &window_, &renderer_) != 0) {
    std::cerr << "Failed to create SDL window or SDL renderer: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
  SDL_SetWindowTitle(window_, window_title.c_str());
}

Graphic::~Graphic() {
  SDL_DestroyTexture(bg_texture_);
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

void Graphic::LoadBGTexture(const std::string path) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
  bg_texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
  if (bg_texture_ == nullptr) {
    std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
}

void Graphic::LoadNameTexture(SDL_Surface surface) {
  name_texture_ = SDL_CreateTextureFromSurface(renderer_, &surface);
  if (name_texture_ == nullptr) {
    std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
  name_rect_ = {
    namebox_rect_.x + (namebox_rect_.w - surface.w) / 2,
    namebox_rect_.y + (namebox_rect_.h - surface.h) / 2,
    surface.w,
    surface.h
  };
}

void Graphic::SetBG() {
  SDL_RenderClear(renderer_);

  // Set background image
  SDL_RenderCopy(renderer_, bg_texture_, nullptr, &bg_rect_);

  // Set textbox
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 150);
  SDL_RenderFillRect(renderer_, &textbox_rect_);

  // Set namebox
  SDL_RenderFillRect(renderer_, &namebox_rect_);

  // Set name
  SDL_RenderCopy(renderer_, name_texture_, nullptr, &name_rect_);
}

void Graphic::RenderBG() {
  SetBG();
  SDL_RenderPresent(renderer_);
}

void Graphic::RenderText(std::vector<TextGraphic> all_lines) {
  SetBG();

  for (auto& line : all_lines) {
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer_, line.surface);
    if (text_texture == nullptr) {
      std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
      SDL_Quit();
      std::exit(EXIT_FAILURE);
    }
    SDL_RenderCopy(renderer_, text_texture, nullptr, &line.rect);
    SDL_DestroyTexture(text_texture);
  }

  SDL_RenderPresent(renderer_);
}

SDL_Rect Graphic::GetTextBoxRect() const {
  return textbox_rect_;
}
