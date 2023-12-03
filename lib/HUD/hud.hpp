#ifndef DefHude
#define DefHude
#include <SDL2/SDL.h>

#include <iostream>

#include "../donjon/donjon.hpp"
#include "../player/player.hpp"
#include "../sprites/sprite.hpp"
class HUD {
 private:
  Player *Joueur;
  Sprite *vieEntiere;
  Sprite *vieDemi;
  Sprite *MapFrame;
  donjon *Don;
  SDL_Rect *rect;

 public:
  HUD(SDL_Renderer *renderer, Player *Joueur, donjon *Don);
  ~HUD();
  void draw(SDL_Renderer *renderer);
};
#endif