#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

class Graphic {
 public:
  Graphic();
  ~Graphic();
  void InitializeWindow(std::string window_title);
  void LoadBGTexture(const std::string path);
  void RenderBG();
  void Render(SDL_Surface* surface, SDL_Rect* rect);
  SDL_Rect GetTextBoxRect() const;

 private:
  void SetBG();

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_Rect bg_rect_;
  SDL_Rect textbox_rect_;
  SDL_Rect namebox_rect_;
  SDL_Texture* bg_texture_;
};
