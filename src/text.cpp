#include <iostream>
#include <chrono>
#include <thread>
#include <codecvt>
#include <locale>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "text.hpp"

Text::Text(std::shared_ptr<Graphic> image)
    : graphic_{image},
      font_{nullptr},
      renderer_{nullptr},
      color_{0, 0, 0, 255} {
  Initialize();
}

Text::~Text() {
  TTF_CloseFont(font_);
}

void Text::Initialize() {
  if (TTF_Init() != 0) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  font_ = TTF_OpenFont(kFontPath.c_str(), 24);
  if (font_ == nullptr) {
    std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
}

void Text::RenderText(const std::string text) {
  std::string text_tmp;
  std::atomic_bool skip = false;
  std::atomic_bool exit = false;
  std::atomic_bool end = false;

  std::thread thread = std::thread([this, &skip, &exit, &end] {
    while (!end) {
      SDL_Event event;
      const Uint8* state = SDL_GetKeyboardState(nullptr);
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          end = true;
          exit = true;
        }
      }
      if (state[SDL_SCANCODE_ESCAPE]) {
        end = true;
        exit = true;
      }
      if (state[SDL_SCANCODE_RETURN]) {
        skip = true;
      }
    }
  });

  // With UTF-8 the size of each character will vary depending on the character.
  // This makes it difficult to calculate the position of the next character.
  // Using UTF-16 when counting the number of characters and using UTF-8 when rendering text is a good way to avoid this problem.
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cv;
  for (auto& c : cv.from_bytes(text)) {
    text_tmp += cv.to_bytes(c);
    SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font_, text_tmp.c_str(), color_);
    if (text_surface == nullptr) {
      std::cerr << "Failed to create text surface: " << SDL_GetError() << std::endl;
      SDL_Quit();
      std::exit(EXIT_FAILURE);
    }
    // decide the text position
    SDL_Rect text_rect = {
      graphic_->GetTextBoxRect().x + 30,
      graphic_->GetTextBoxRect().y + 20,
      text_surface->w,
      text_surface->h
    };
    graphic_->Render(text_surface, &text_rect);

    if (skip) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    if (exit) break;
  }

  // TODO: Need to refactor
  end = true;
  thread.join();
  if (exit) {
    std::cout << "Quit" << std::endl;
    SDL_Quit();
    std::exit(EXIT_SUCCESS);
  }
}
