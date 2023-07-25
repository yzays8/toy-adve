#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "text.hpp"
#include "graphic.hpp"
#include "data.hpp"

class Engine {
 public:
  Engine(std::string game);
  ~Engine();
  bool Run();

 private:
  std::unique_ptr<Data> data_;
  std::shared_ptr<Graphic> graphic_;
  std::unique_ptr<Text> text_;
};
