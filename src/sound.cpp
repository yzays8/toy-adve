#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "sound.hpp"

Sound::Sound() : audio_{nullptr} {
  if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
    std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
    Mix_Quit();
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
}

Sound::~Sound() {
  Mix_HaltMusic();
  Mix_FreeMusic(audio_);
  Mix_CloseAudio();
  Mix_Quit();
  SDL_Quit();
}

void Sound::Load(const std::string path) {
  audio_ = Mix_LoadMUS(path.c_str());
  if (audio_ == nullptr) {
    std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }
}

void Sound::Play() {
  // loop infinitely
  Mix_PlayMusic(audio_, -1);
}

void Sound::Pause() {
  Mix_HaltMusic();
}

void Sound::UnLoad() {
  if (audio_ == nullptr) {
    return;
  }
  Mix_HaltMusic();
  Mix_FreeMusic(audio_);
};
