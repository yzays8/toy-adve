#pragma once

#include <vector>
#include <nlohmann/json.hpp>

struct GameScene {
  std::string image;
  std::string speaker;
  std::vector<std::string> text;
};

class Data {
 public:
  Data(const std::string path);
  std::string GetTitle() const;
  std::string GetFont() const;
  std::vector<GameScene>& GetScenes();

 private:
  nlohmann::json game_;
  std::string title_;
  std::string font_;
  std::vector<GameScene> scenes_;
};
