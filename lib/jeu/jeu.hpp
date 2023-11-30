#ifndef MENU_HPP
#define MENU_HPP

#include "../Variables/variables.hpp"
#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"

class Jeu: public Gamemode {
 public:
  Jeu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);
  void Init();
  void Pause(std::string* Gamemode);
  world* Monde;
  void handleEvents(std::string* Gamemode);
  void render();
  void update();
  void unpause();
};

#endif