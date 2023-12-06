#include "sprite.hpp"

#include "../Variables/variables.hpp"
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
  this->realw = 0;
  this->realh = 0;
  this->lien = "";
  this->Rezise = false;
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
  this->Rezise = false;
  this->srcRect = new SDL_Rect();
  this->realw = 0;
  this->realh = 0;

  this->lien = lien;
  this->Img = nullptr;
}

Sprite::Sprite(int x, int y, int w, int h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;

  this->rect = new SDL_Rect();
  this->rect->x = x;
  this->rect->y = y;
  this->rect->w = w;
  this->rect->h = h;
  this->Rezise = false;
  this->srcRect = new SDL_Rect();
  this->realw = 0;
  this->realh = 0;
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
  if(!this->Rezise) {
    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    this->srcRect->x = 0;
    this->srcRect->y = 0;
    this->srcRect->w = width;
    this->srcRect->h = height;

    this->realw = width;
    this->realh = height;
  }
}

void Sprite::loadImage(SDL_Renderer* Renderer, SDL_Texture* Img) {
  if(Img == nullptr) {
    std::cerr << "Échec du chargement de l'image." << std::endl;
  }
  this->SetImage(Img);
  if(!this->Rezise) {
    int width = 0;
    int height = 0;
    SDL_QueryTexture(Img, NULL, NULL, &width, &height);
    this->srcRect->x = 0;
    this->srcRect->y = 0;
    this->srcRect->w = width;
    this->srcRect->h = height;

    this->realw = width;
    this->realh = height;
  }
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
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = this->getWidth();
  rect.h = this->getHeight();
  SDL_RenderCopyEx(Renderer, this->GetImg(), this->getsrcRect(), &rect, 0, NULL, SDL_FLIP_NONE);
}

void Sprite::selfDraw(SDL_Renderer* Renderer, int x, int y, SDL_Rect Frame) {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  // rect.w = std::min(this->getWidth() - (Frame.x - x), this->getWidth());
  // rect.h = std::min(this->getHeight() - (Frame.y - y), this->getHeight());

  rect.h = this->getHeight();

  if(x < Frame.x && x + this->getWidth() < Frame.x) {
    rect.w = 0;
    this->srcRect->x = realw;
  } else if(x < Frame.x && x + this->getWidth() > Frame.x) {
    rect.x = Frame.x + 5;
    rect.w = this->getWidth() - (rect.x - x);
    this->srcRect->x = 20;
  } else if(x > Frame.x + Frame.w) {
    rect.w = 0;
    this->srcRect->x = -realw;
  } else if(x + this->getWidth() > Frame.x + Frame.w) {
    rect.w = this->getWidth() - (x + this->getWidth() - (Frame.x + Frame.w) + 5);
    this->srcRect->x = realw - (realw + tailleCase);
  } else {
    rect.w = this->getWidth();
    this->srcRect->x = 0;
  }

  if(y < Frame.y && y + this->getHeight() < Frame.y) {
    rect.h = 0;
    this->srcRect->y = realh;
  } else if(y < Frame.y && y + this->getHeight() > Frame.y) {
    rect.y = Frame.y + 7;
    rect.h = this->getHeight() - (rect.y - y);
    this->srcRect->y = 20;
  } else if(y > Frame.y + Frame.h) {
    rect.h = 0;
    this->srcRect->y = -realh;
  } else if(y + this->getHeight() > Frame.y + Frame.h) {
    rect.h = this->getHeight() - (y + this->getHeight() - (Frame.y + Frame.h) + 7);
    this->srcRect->y = realh - (realh + tailleCase);
  } else {
    rect.h = this->getHeight();
    this->srcRect->y = 0;
  }

  SDL_RenderCopyEx(Renderer, this->GetImg(), this->getsrcRect(), &rect, 0, NULL, SDL_FLIP_NONE);
}

void Sprite::setSrcRect(int x, int y, int w, int h) {
  this->srcRect->x = x;
  this->srcRect->y = y;
  this->srcRect->w = w;
  this->srcRect->h = h;
  this->Rezise = true;
}

int Sprite::getWidth() { return this->w; }

int Sprite::getHeight() { return this->h; }

bool Sprite::isColliding(int x, int y, int w, int h) {
  if((this->x < x + w) && (this->x + this->w > x) && (this->y < y + h) && (this->y + this->h > y)) {
    return true;
  }
  return false;
}