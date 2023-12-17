#ifndef Texte_HPP
#define Texte_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

class texte {
 private:
  std::string text;
  SDL_Color color;
  SDL_Rect rect;
  SDL_Surface* surface;
  SDL_Texture* texture;
  TTF_Font* font;
  SDL_Renderer* Renderer;
  bool autoAdjust;
  bool centered;

 public:
  texte(SDL_Renderer* Renderer, std::string text, SDL_Color color, SDL_Rect rect, bool autoAdjust, bool centered = false);
  ~texte();
  void setText(std::string text, int x, int y, int w, int h);
  void setColor(SDL_Color color);
  int getX();
  int getY();
  int getW();
  int getH();

  void draw(SDL_Renderer* Renderer);
};

#endif
