#ifndef pause_HPP
#define pause_HPP
#include <SDL2/SDL.h>

#include "../button/button.hpp"
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"

class Mpause: public Gamemode {
 public:
  Mpause(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);
  ~Mpause();
  Sprite* Image;
  Bouton* play;
  Bouton* exit;
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