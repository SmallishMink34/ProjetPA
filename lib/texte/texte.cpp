#include "texte.hpp"

texte::texte(SDL_Renderer* Renderer, std::string text, SDL_Color color, SDL_Rect rect) {
  this->text = text;
  this->color = color;
  this->rect = rect;
  this->Renderer = Renderer;

  this->font = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  if(this->font == NULL) {
    std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
  } else {
    this->surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
    if(this->surface == NULL) {
      std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
      this->texture = SDL_CreateTextureFromSurface(Renderer, this->surface);
      if(this->texture == NULL) {
        std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
      }
    }
  }
}

void texte::setText(std::string text) {
  this->text = text;
  this->surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
  this->texture = SDL_CreateTextureFromSurface(Renderer, this->surface);
}

void texte::setColor(SDL_Color color) {
  this->color = color;
  this->surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
  this->texture = SDL_CreateTextureFromSurface(Renderer, this->surface);
}

void texte::draw(SDL_Renderer* Renderer) { SDL_RenderCopy(Renderer, this->texture, NULL, &this->rect); }

texte::~texte() {
  SDL_FreeSurface(this->surface);
  SDL_DestroyTexture(this->texture);
  TTF_CloseFont(this->font);
}