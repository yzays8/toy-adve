#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"

int main() {
  auto engine = std::make_unique<Engine>();
  bool success = engine->Run();
  if (!success) {
    std::cerr << "Exit with error" << std::endl;
    return 1;
  }
}
