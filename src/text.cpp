#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
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
  std::atomic_bool fast_forward = false;
  std::atomic_bool exit = false;
  std::atomic_bool end_rendering = false;

  std::thread th_rendering_text = std::thread([this, &texts, &fast_forward, &exit, &end_rendering] {
    std::vector<TextGraphic> data;
    int line_num = 0;
    for (auto& text: texts) {
      SDL_Surface* text_surface = nullptr;
      SDL_Rect text_rect;

      // Append one character to the text line in each loop
      std::string text_tmp;
      for (size_t i = 0; i < text.size();) {
        // Handle UTF-8
        int size_of_char = 1;
        if ((text[i] & 0xE0) == 0xC0) {
          size_of_char = 2;
        } else if ((text[i] & 0xF0) == 0xE0) {
          size_of_char = 3;
        } else if ((text[i] & 0xF8) == 0xF0) {
          size_of_char = 4;
        }
        if (i + size_of_char > text.size()) {
          break;
        }

        text_tmp.append(text.substr(i, size_of_char));
        i += size_of_char;

        text_surface = TTF_RenderUTF8_Blended(font_, text_tmp.c_str(), color_);
        if (text_surface == nullptr) {
          std::cerr << "Failed to create text surface: " << SDL_GetError() << std::endl;
          SDL_Quit();
          std::exit(EXIT_FAILURE);
        }

        // decide the text position
        text_rect = {
          graphic_->GetTextBoxRect().x + 30,
          graphic_->GetTextBoxRect().y + 20 + text_surface->h * line_num,
          text_surface->w,
          text_surface->h
        };
        data.push_back({text_surface, text_rect});

        graphic_->RenderText(data);
        data.pop_back();

        if (fast_forward) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } else {
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (exit) break;
      }

      if (exit) break;
      data.push_back({text_surface, text_rect});  // add an entire text line
      ++line_num;
    }

    for (auto& text : data) {
      SDL_FreeSurface(text.surface);
    }

    end_rendering = true;
  });

  while (!end_rendering) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          end_rendering = true;
          exit = true;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_RETURN) {
            fast_forward = true;
          }
          break;
      }
    }
  }

  th_rendering_text.join();
  if (exit) {
    std::cout << "Quit" << std::endl;
    SDL_Quit();
    std::exit(EXIT_SUCCESS);
  }
}
