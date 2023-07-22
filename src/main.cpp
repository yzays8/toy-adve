#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./game <path to game file>" << std::endl;
    return 1;
  }
  auto engine = std::make_unique<Engine>(argv[1]);
  bool success = engine->Run();
  if (!success) {
    std::cerr << "Exit with error" << std::endl;
    return 1;
  }
}
