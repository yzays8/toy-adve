#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "data.hpp"

namespace fs = std::filesystem;

Data::Data(const std::string path) {
  if (!fs::is_regular_file(path)) {
    std::cerr << path << " is not a regular file" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::ifstream ifs{path, std::ios::in};
  if (!ifs.is_open()) {
    std::cout << "Failed to open game json file: " << path << std::endl;
    std::exit(EXIT_FAILURE);
  }
  game_ = nlohmann::json::parse(ifs);

  title_ = game_.at("title");

  fs::path dir_path{path};
  fs::path tmp_path = game_.at("font");
  font_ = dir_path.remove_filename() / tmp_path;

  auto scenes = game_.at("scenes");
  for (auto& scene : scenes) {
    GameScene tmp;

    fs::path tmp_img_path = scene.at("image");
    tmp.image = dir_path.remove_filename() / tmp_img_path;

    fs::path tmp_sound_path = scene.at("music");
    tmp.sound = dir_path.remove_filename() / tmp_sound_path;

    tmp.speaker = scene.at("speaker");
    for (auto& text : scene.at("text")) {
      tmp.text.push_back(text);
    }
    scenes_.push_back(tmp);
  }
  std::cout << "Loaded " << scenes_.size() << " scenes" << std::endl;
}

std::string Data::GetTitle() const {
  return title_;
}

std::string Data::GetFont() const {
  return font_;
}

std::vector<GameScene>& Data::GetScenes() {
  return scenes_;
}
