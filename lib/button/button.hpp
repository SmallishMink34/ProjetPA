// button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

#include "../display/display.hpp"
#include "../sprites/sprite.hpp"

class Bouton {
 public:
  Bouton();
  Bouton(SDL_Renderer* Renderer, const char* lien, int x, int y, int w, int h);
  ~Bouton();

  SDL_Rect* getRect();
  int getWidth();
  int getHeight();

  void gererFin(SDL_Event* evenement, SDL_Renderer* rendu, bool* quit);
  void gererPlay(SDL_Event* evenement, SDL_Renderer* rendu, bool* var);
  bool isColliding(int mouseX, int mouseY);
  int getY();
  int getX();
  void selfDraw(SDL_Renderer* gRenderer);
  void setSurface(int x, int y, int w, int h);

 private:
  int etat;
  Sprite image;
  SDL_Rect rect;
};

#endif  // BUTTON_HPP
