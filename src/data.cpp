#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "data.hpp"

Data::Data(const std::string path) {
  if (std::filesystem::is_regular_file(path)) {
    std::cout << "Failed to load game json file" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::fstream ifs{path, std::ios::in};
  game_ = nlohmann::json::parse(ifs);
}
