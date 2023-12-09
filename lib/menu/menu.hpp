#ifndef MENUE_HPP
#define MENUE_HPP
#include <SDL2/SDL.h>

#include "../button/button.hpp"
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"

class menu: public Gamemode {
 public:
  menu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);
  ~menu();

  Sprite Image;
  Sprite titre;
  Bouton play;
  Bouton exit;
  SDL_Event evenement;

  void Init();
  void handleEvents(std::string* Gamemode);
  void render();
  void update();
  void unpause();
  int Real_W;
  int Real_H;
  bool var;
};

#endif