#include <iostream>
#include <memory>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"

Engine::Engine()
  : graphic_{std::make_shared<Graphic>()},
    text_{std::make_unique<Text>(graphic_)} {}

Engine::~Engine() {
  SDL_Quit();
}

void Engine::Run() {
  // render background
  graphic_->RenderBG();

  // show text
  const std::string t = R"(あいうえお Test test Test!!!!!!!あいうえお Test test Test!!!!!!!)";
  text_->RenderText(t);

  // wait for next event
  for (;;) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if ((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_ESCAPE)) {
        std::cout << "Quit" << std::endl;
        break;
      }
    }
  }
}
