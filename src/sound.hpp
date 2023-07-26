#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound {
 public:
  Sound();
  ~Sound();
  void Load(const std::string path);
  void UnLoad();
  void Play();
  void Pause();

 private:
  Mix_Music* audio_;
};
