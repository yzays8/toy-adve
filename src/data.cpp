#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "data.hpp"

Data::Data(const std::string path) {
  if (!std::filesystem::is_regular_file(path)) {
    std::cerr << "Failed to load game json file: " << path << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::ifstream ifs(path, std::ios::in);
  if (!ifs.is_open()) {
    std::cout << "Failed to open game json file: " << path << std::endl;
    std::exit(EXIT_FAILURE);
  }
  game_ = nlohmann::json::parse(ifs);
  std::cout << "Loaded game json file: " << path << std::endl;

  auto scenes = game_.at("game");
  for (auto& scene : scenes) {
    scenes_.push_back({scene.at("image"), scene.at("text")});
  }
  for (auto& scene : scenes_) {
    std::cout << scene.image << ": " << scene.text << std::endl;
  }
}

nlohmann::json& Data::GetGame() {
  return game_;
}

std::vector<GameScene>& Data::GetScenes() {
  return scenes_;
}
