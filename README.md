# toy-adve

## Overview

This is a toy ADV (adventure game) engine. Game title, font, images and scripts can be specified in JSON file.

## Requirements

### Debian (Ubuntu)

SDL2 and [JSON for Modern C++](https://github.com/nlohmann/json) are required.

```sh
sudo apt install libsdl2-dev
sudo apt install nlohmann-json3-dev
```

### Mac

```sh
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer sdl2_gfx
brew install nlohmann-json
```

## Build

```sh
make
```

## Run

```sh
make run FILE=<file_path>
```

To run sample game:

```sh
make test
```
