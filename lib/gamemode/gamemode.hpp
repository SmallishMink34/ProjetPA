#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "../Variables/variables.hpp"
#include "../world/world.hpp"

class Gamemode {
 public:
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  bool quit;
  bool isLoaded;
  Variable* Var;
  Gamemode();

  virtual void handleEvents(std::string* Gamemode) = 0;
  virtual void Init() = 0;
  virtual void render() = 0;
  virtual void update() = 0;
  virtual void unpause() = 0;
  virtual ~Gamemode() = 0;
};

#endif