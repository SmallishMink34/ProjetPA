#include "texte.hpp"

texte::texte(SDL_Renderer* Renderer, std::string text, SDL_Color color, SDL_Rect rect, bool autoAdjust, bool centered) {
  this->text = text;
  this->color = color;
  this->rect = rect;
  this->Renderer = Renderer;
  this->autoAdjust = autoAdjust;
  this->font = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  this->centered = centered;
  this->surface = nullptr;
  this->texture = nullptr;
  if(this->font == NULL) {
    std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
  } else {
    setText(this->text);
  }
}

void texte::setText(std::string text) {
  this->text = text;

  if(this->texture != nullptr) {
    SDL_DestroyTexture(this->texture);
  }
  if(this->surface != nullptr) {
    SDL_FreeSurface(this->surface);
  }

  this->surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
  if(this->surface == NULL) {
    std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
  } else {
    this->texture = SDL_CreateTextureFromSurface(Renderer, this->surface);
    if(this->texture == NULL) {
      std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
    }
  }
  if(this->autoAdjust) {
    this->rect.w = this->rect.w * this->text.length() / 2;
  }
  if(this->centered) {
    this->rect.x = this->rect.x - this->rect.w / 2;
  }
}

void texte::setColor(SDL_Color color) {
  this->color = color;
  this->surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
  this->texture = SDL_CreateTextureFromSurface(Renderer, this->surface);
}

void texte::draw(SDL_Renderer* Renderer) { SDL_RenderCopy(Renderer, this->texture, NULL, &this->rect); }

int texte::getX() { return this->rect.x; }

int texte::getY() { return this->rect.y; }

int texte::getW() { return this->rect.w; }

int texte::getH() { return this->rect.h; }

texte::~texte() {
  SDL_FreeSurface(this->surface);
  SDL_DestroyTexture(this->texture);
  TTF_CloseFont(this->font);
}