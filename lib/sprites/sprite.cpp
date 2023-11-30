#include "sprite.hpp"

#include "../display/display.hpp"

Sprite::Sprite() {
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
  this->rect = new SDL_Rect();
  this->rect->x = 0;
  this->rect->y = 0;
  this->rect->w = 0;
  this->rect->h = 0;
  this->lien = "";
  this->Img = nullptr;
}

Sprite::Sprite(std::string lien, int x, int y, int w, int h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;

  this->rect = new SDL_Rect();
  this->rect->x = x;
  this->rect->y = y;
  this->rect->w = w;
  this->rect->h = h;

  this->srcRect = new SDL_Rect();
  this->setSrcRect(0, 0, w, h);

  this->lien = lien;
  this->Img = nullptr;
}

void Sprite::DrawRepeat(SDL_Renderer* Renderer, int w, int h, int dx, int dy) {
  for(int i = 0; i < w; i++)
    for(int j = 0; j < h; j++) this->selfDraw(Renderer, i * getWidth() - dx, j * getHeight() - dy);
}

void Sprite::loadImage(SDL_Renderer* Renderer) {
  SDL_Texture* texture = loadTexture(Renderer, this->lien);
  if(texture == nullptr) {
    std::cerr << "Échec du chargement de l'image." << std::endl;
  }
  this->SetImage(texture);
}

void Sprite::SetImage(SDL_Texture* Img) { this->Img = Img; }

void Sprite::Moveto(int x, int y) {
  this->x = x;
  this->y = y;
  this->rect->x = x;
  this->rect->y = y;
}
std::string Sprite::Getlink() { return this->lien; }

SDL_Rect* Sprite::getRect() { return this->rect; }

SDL_Rect* Sprite::getsrcRect() { return this->srcRect; }

SDL_Texture* Sprite::GetImg() { return this->Img; }

void Sprite::selfDraw(SDL_Renderer* Renderer) { SDL_RenderCopyEx(Renderer, this->GetImg(), this->getsrcRect(), this->getRect(), 0, NULL, SDL_FLIP_NONE); }

void Sprite::selfDraw(SDL_Renderer* Renderer, int x, int y) {
  SDL_Rect* rect = new SDL_Rect();
  rect->x = x;
  rect->y = y;
  rect->w = this->getWidth();
  rect->h = this->getHeight();

  SDL_RenderCopyEx(Renderer, this->GetImg(), this->getsrcRect(), rect, 0, NULL, SDL_FLIP_NONE);
}

void Sprite::setSrcRect(int x, int y, int w, int h) {
  this->srcRect->x = x;
  this->srcRect->y = y;
  this->srcRect->w = w;
  this->srcRect->h = h;
}

int Sprite::getWidth() { return this->w; }

int Sprite::getHeight() { return this->h; }

bool Sprite::isColliding(int x, int y, int w, int h) {
  if((this->x < x + w) && (this->x + this->w > x) && (this->y < y + h) && (this->y + this->h > y)) {
    return true;
  }
  return false;
}