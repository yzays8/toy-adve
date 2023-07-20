#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;
const std::string kWindowTitle{"Toy ADV Engine"};

class Graphic {
 public:
  Graphic();
  ~Graphic();
  void LoadBGTexture(const std::string path);
  void RenderBG();
  void Render(SDL_Surface* surface, SDL_Rect* rect);
  SDL_Rect GetTextBoxRect() const;

 private:
  void InitializeWindow();
  void SetBG();

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_Rect bg_rect_;
  SDL_Rect textbox_rect_;
  SDL_Rect namebox_rect_;
  SDL_Texture* bg_texture_;
};
