#pragma once

// sudo apt install nlohmann-json3-dev
#include <nlohmann/json.hpp>

class Data {
 public:
  Data(const std::string path);
  ~Data();

 private:
  nlohmann::json game_;
};
