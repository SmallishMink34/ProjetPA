#include "tile.hpp"

#include <SDL2/SDL.h>

Tile::Tile(SDL_Renderer* Renderer, std::string image, int x, int y, int w, int h) {
  this->sprite = new Sprite(image, x, y, w, h);
  this->sprite->loadImage(Renderer);
  this->rect = new SDL_Rect({x, y, w, h});
};

Tile::Tile(SDL_Renderer* Renderer, tile t, int x, int y, int w, int h) {
  this->sprite = new Sprite(x, y, w, h);
  this->sprite->loadImage(Renderer, t.sheet);
  this->sprite->setSrcRect(t.tx, t.ty, t.width, t.height);
  this->rect = new SDL_Rect({x, y, w, h});
};

int Tile::getX() { return this->rect->x; }

int Tile::getY() { return this->rect->y; }

int Tile::getWidth() { return this->rect->w; }

int Tile::getHeight() { return this->rect->h; }

void Tile::draw(SDL_Renderer* renderer, int dx, int dy) { this->sprite->selfDraw(renderer, this->rect->x - dx, this->rect->y - dy); };

Tile::~Tile() {
  delete sprite;
  delete rect;
}