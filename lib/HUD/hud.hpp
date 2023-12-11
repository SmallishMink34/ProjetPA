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

  Variable *Var;
  SDL_Texture *TextureScore;
  SDL_Rect Score_rect;

  TTF_Font* Sans = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  SDL_Color Blue = {0, 191, 255};

 public:
  HUD(SDL_Renderer *renderer, Player *Joueur, donjon *Don);
  ~HUD();
  void draw(SDL_Renderer *renderer);
  void update(SDL_Renderer* renderer);
  char scoreText[20];

};
#endif