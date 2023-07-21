#pragma once

#include <vector>

// sudo apt install nlohmann-json3-dev
#include <nlohmann/json.hpp>

struct GameScene {
  std::string image;
  std::string speaker;
  std::vector<std::string> text;
};

class Data {
 public:
  Data(const std::string path);
  nlohmann::json& GetGame();
  std::string GetTitle();
  std::vector<GameScene>& GetScenes();

 private:
  nlohmann::json game_;
  std::string title_;
  std::vector<GameScene> scenes_;
};
