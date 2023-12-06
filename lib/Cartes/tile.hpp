#include <SDL2/SDL.h>

#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"

class Tile {
 private:
  Sprite* sprite;
  SDL_Rect* rect;

 public:
  Tile(SDL_Renderer* Renderer, std::string image, int x, int y, int w, int h);
  Tile(SDL_Renderer* Renderer, tile t, int x, int y, int w, int h);

  int getX();
  int getY();
  int getWidth();
  int getHeight();

  void draw(SDL_Renderer* renderer, int dx, int dy);
};
