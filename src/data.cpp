#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "data.hpp"

Data::Data(const std::string path) {
  if (!std::filesystem::is_regular_file(path)) {
    std::cerr << path << "is not a regular file" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::ifstream ifs(path, std::ios::in);
  if (!ifs.is_open()) {
    std::cout << "Failed to open game json file: " << path << std::endl;
    std::exit(EXIT_FAILURE);
  }
  game_ = nlohmann::json::parse(ifs);

  title_ = game_.at("title");

  auto scenes = game_.at("game");
  for (auto& scene : scenes) {
    GameScene tmp;
    tmp.image = scene.at("image");
    tmp.speaker = scene.at("speaker");
    for (auto& text : scene.at("text")) {
      tmp.text.push_back(text);
    }
    scenes_.push_back(tmp);
  }
  std::cout << "Loaded " << scenes_.size() << " scenes" << std::endl;
}

nlohmann::json& Data::GetGame() {
  return game_;
}

std::string Data::GetTitle() {
  return title_;
}

std::vector<GameScene>& Data::GetScenes() {
  return scenes_;
}
