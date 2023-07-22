#include <iostream>
#include <memory>
#include <thread>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"
#include "data.hpp"

Engine::Engine(std::string game)
    : data_{std::make_unique<Data>(game)},
      graphic_{std::make_shared<Graphic>()},
      text_{std::make_unique<Text>(graphic_, data_->GetFont())} {}

Engine::~Engine() {
  SDL_Quit();
}

bool Engine::Run() {
  graphic_->InitializeWindow(data_->GetTitle());

  for (auto& scene : data_->GetScenes()) {
    // render background
    graphic_->LoadBGTexture(scene.image);
    graphic_->LoadNameTexture(text_->GetNameSurface(scene.speaker, {0, 0, 255, 255}));
    graphic_->RenderBG();

    // show text
    text_->RenderText(scene.text);

    // blink triangle
    std::atomic_bool end_of_thread = false;
    std::thread th_triangle = std::thread([this, &end_of_thread]() {
      SDL_Texture* base_texture = graphic_->CreateCurrentTexture();
      auto wait_for_10Xms = [&end_of_thread](int x) {
        for (int i = 0; i < x; ++i) {
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
          if (end_of_thread) break;
        }
      };
      while (!end_of_thread) {
        graphic_->RenderTriangle(base_texture, true);
        wait_for_10Xms(50);
        graphic_->RenderTriangle(base_texture, false);
        wait_for_10Xms(50);
      }
      SDL_DestroyTexture(base_texture);
    });

    // wait for next event
    bool move_to_next = false;
    for (;;) {
      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            std::cout << "Quit" << std::endl;
            end_of_thread = true;
            th_triangle.join();
            return true;
          case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN) {
              move_to_next = true;
              end_of_thread = true;
              th_triangle.join();
            }
            break;
        }
      }

      if (move_to_next) break;
    }
  }

  return true;
}
