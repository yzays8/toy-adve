#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <codecvt>
#include <locale>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "text.hpp"

Text::Text(std::shared_ptr<Graphic> image, std::string font_path)
    : graphic_{image},
      font_{nullptr},
      color_{0, 0, 0, 255} {
  Initialize(font_path);
}

Text::~Text() {
  TTF_CloseFont(font_);
}

void Text::Initialize(std::string font_path) {
  if (TTF_Init() != 0) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  font_ = TTF_OpenFont(font_path.c_str(), 24);
  if (font_ == nullptr) {
    std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
}

SDL_Surface* Text::GetNameSurface(const std::string name, SDL_Color color) {
  SDL_Surface* name_surface = TTF_RenderUTF8_Blended(font_, name.c_str(), color);
  if (name_surface == nullptr) {
    std::cerr << "Failed to create name surface: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
  return name_surface;
}

void Text::RenderText(const std::vector<std::string> texts) {
  std::atomic_bool skip = false;
  std::atomic_bool exit = false;
  std::atomic_bool end = false;

  std::thread thread = std::thread([this, &texts, &skip, &exit, &end] {
    std::vector<TextGraphic> data;

    // With UTF-8 the size of each character will vary depending on the character.
    // This makes it difficult to calculate the position of the next character.
    // Using UTF-16 when counting the number of characters and using UTF-8 when rendering text is a good way to avoid this problem.
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cv;
    int i = 0;
    for (auto& text: texts) {
      SDL_Surface* text_surface;
      SDL_Rect text_rect;
      std::string text_tmp;
      for (auto& c : cv.from_bytes(text)) {
        text_tmp += cv.to_bytes(c);
        text_surface = TTF_RenderUTF8_Blended(font_, text_tmp.c_str(), color_);
        if (text_surface == nullptr) {
          std::cerr << "Failed to create text surface: " << SDL_GetError() << std::endl;
          SDL_Quit();
          std::exit(EXIT_FAILURE);
        }

        // decide the text position
        text_rect = {
          graphic_->GetTextBoxRect().x + 30,
          graphic_->GetTextBoxRect().y + 20 + text_surface->h * i,
          text_surface->w,
          text_surface->h
        };
        data.push_back({text_surface, text_rect});

        graphic_->RenderText(data);
        data.pop_back();

        if (skip) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } else {
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (exit) break;
      }
      if (exit) break;
      data.push_back({text_surface, text_rect});  // add an entire text line
      ++i;
    }

    for (auto& text : data) {
      SDL_FreeSurface(text.surface);
    }

    end = true;
  });

  while (!end) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          end = true;
          exit = true;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_RETURN) {
            skip = true;
          }
          break;
      }
    }
  }

  thread.join();
  if (exit) {
    std::cout << "Quit" << std::endl;
    SDL_Quit();
    std::exit(EXIT_SUCCESS);
  }
}
