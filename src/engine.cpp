#include <iostream>
#include <memory>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"
#include "data.hpp"

Engine::Engine()
    : graphic_{std::make_shared<Graphic>()},
      text_{std::make_unique<Text>(graphic_)},
      data_{std::make_unique<Data>("../games/sample.json")} {}

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
    //TODO: multiple lines
    text_->RenderText(scene.text);

    // wait for next event
    bool next = false;
    for (;;) {
      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            std::cout << "Quit" << std::endl;
            return true;
          case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN) {
              next = true;
            }
            break;
        }
      }

      if (next) break;
    }
  }

  return true;
}
