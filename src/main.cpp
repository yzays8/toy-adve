#include <iostream>
#include <memory>

#include "engine.hpp"
#include "text.hpp"
#include "graphic.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path to game file>" << std::endl;
    return 1;
  }

  auto engine = std::make_unique<Engine>(argv[1]);
  bool success = engine->Run();
  if (!success) {
    std::cerr << "Exit with error" << std::endl;
    return 1;
  }
}
