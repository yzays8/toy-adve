#include <iostream>
#include <memory>
#include <thread>
#include <SDL2/SDL.h>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"
#include "data.hpp"
#include "sound.hpp"

Engine::Engine(std::string game)
    : data_{std::make_unique<Data>(game)},
      graphic_{std::make_shared<Graphic>()},
      text_{std::make_unique<Text>(graphic_, data_->GetFont())},
      sound_{std::make_unique<Sound>()} {}

Engine::~Engine() {
  SDL_Quit();
}

bool Engine::Run() {
  graphic_->InitializeWindow(data_->GetTitle());

  std::string prev_sound{};
  for (auto& scene : data_->GetScenes()) {
    // render background
    graphic_->LoadBGTexture(scene.image);
    graphic_->LoadNameTexture(text_->GetNameSurface(scene.speaker, {0, 0, 255, 255}));
    graphic_->RenderBG();

    // play music
    if (scene.sound != prev_sound) {
      sound_->UnLoad();
      sound_->Load(scene.sound);
      sound_->Play();
      prev_sound = scene.sound;
    }

    // show text
    text_->RenderText(scene.text);

    // blink triangle
    std::atomic_bool end_of_thread = false;
    std::atomic_bool show_bg_image = false;
    std::thread th_triangle = std::thread([this, &end_of_thread, &show_bg_image]() {
      SDL_Texture* base_texture = graphic_->CreateCurrentTexture();
      auto sleep_for_10Xms = [this, &end_of_thread, &show_bg_image](int x) {
        for (int i = 0; i < x; ++i) {
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
          if (end_of_thread) {
            break;
          } else if (show_bg_image) {
            this->graphic_->RenderOnlyBGTexture();
            while(show_bg_image && !end_of_thread);
          }
        }
      };
      while (!end_of_thread) {
        graphic_->RenderTriangle(base_texture, true);
        sleep_for_10Xms(50);
        graphic_->RenderTriangle(base_texture, false);
        sleep_for_10Xms(50);
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
            switch (event.key.keysym.sym) {
              case SDLK_RETURN:
                move_to_next = true;
                end_of_thread = true;
                th_triangle.join();
                break;
              case SDLK_SPACE:
                show_bg_image = !show_bg_image;
                break;
            }
            break;
        }
      }

      if (move_to_next) break;
    }
  }

  return true;
}
