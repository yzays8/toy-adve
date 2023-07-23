#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

struct TextGraphic {
  SDL_Surface* surface;
  SDL_Rect rect;
};

class Graphic {
 public:
  Graphic();
  ~Graphic();
  void InitializeWindow(std::string window_title);
  void LoadBGTexture(const std::string path);
  void LoadNameTexture(SDL_Surface* surface);
  void RenderBG();
  void RenderText(std::vector<TextGraphic>);
  void RenderTriangle(SDL_Texture* base_texture, bool render_triangle);
  SDL_Texture* CreateCurrentTexture();
  SDL_Rect GetTextBoxRect() const;

 private:
  void SetBG();

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_Rect bg_rect_;
  SDL_Rect textbox_rect_;
  SDL_Rect namebox_rect_;
  SDL_Rect name_rect_;
  SDL_Texture* bg_texture_;
  SDL_Texture* name_texture_;
};
