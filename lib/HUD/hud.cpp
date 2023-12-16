#include "hud.hpp"

#include <SDL2/SDL_ttf.h>

#include "../Variables/variables.hpp"

HUD::HUD(SDL_Renderer* renderer, Player* Joueur, donjon* Don, Variable* Var) {
  this->Joueur = Joueur;
  this->Don = Don;
  vieEntiere = new Sprite("src/Images/Player/coeur.png", 0, 0, 64, 64);
  vieEntiere->loadImage(renderer);
  vieDemi = new Sprite("src/Images/Player/coeur2.png", 0, 0, 64, 64);
  vieDemi->loadImage(renderer);

  MapFrame = new Sprite("src/Images/HUD/MiniMapFrame.png", Windows_W - 266, 10, 256, 256);
  MapFrame->loadImage(renderer);
  rect = new SDL_Rect;
  rect->x = MapFrame->getRect()->x + 10;
  rect->y = MapFrame->getRect()->y + 10;
  rect->w = MapFrame->getRect()->w - 20;
  rect->h = MapFrame->getRect()->h - 20;

  sprintf(scoreText, "Score: %d", Joueur->getScore());
  SDL_Surface* SurfaceScore = TTF_RenderText_Solid(Sans, scoreText, Blue);
  TextureScore = SDL_CreateTextureFromSurface(renderer, SurfaceScore);
  Score_rect.x = Var->Real_W - 210;
  Score_rect.y = Var->Real_W / 5;
  Score_rect.w = 180;
  Score_rect.h = 120;

  SDL_FreeSurface(SurfaceScore);
}

void HUD::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, rect);
  update(renderer);
  this->Don->draw_tree(renderer, this->Don->initial_Node,
                       MapFrame->getRect()->x + MapFrame->getRect()->w / 2 - this->Don->getActualRoomNode(this->Don->initial_Node)->getRoom()->getX() * tailleCase,
                       MapFrame->getRect()->y + MapFrame->getRect()->h / 2 - this->Don->getActualRoomNode(this->Don->initial_Node)->getRoom()->getY() * tailleCase,
                       *MapFrame->getRect());

  MapFrame->selfDraw(renderer);
  int compteur = 0;
  for(int i = 0; i <= this->Joueur->getVie(); i++) {
    if(i % 2 == 0 && i != 0) {
      this->vieEntiere->selfDraw(renderer, 10 + compteur * 45, 10);
      compteur++;
    } else if(i == this->Joueur->getVie()) {
      this->vieDemi->selfDraw(renderer, 10 + compteur * 45, 10);
    }
  }
  SDL_RenderCopy(renderer, TextureScore, NULL, &Score_rect);
}

void HUD::update(SDL_Renderer* renderer) {
  char scoreText[20];
  sprintf(scoreText, "Score : %d", Joueur->getScore() / 120);

  Joueur->IncrementScore(1);

  SDL_DestroyTexture(TextureScore);

  SDL_Surface* SurfaceScore = TTF_RenderText_Solid(Sans, scoreText, Blue);
  TextureScore = SDL_CreateTextureFromSurface(renderer, SurfaceScore);

  Score_rect.w = SurfaceScore->w;
  Score_rect.h = SurfaceScore->h;

  SDL_FreeSurface(SurfaceScore);
}
HUD::~HUD() {
  delete vieEntiere;
  delete vieDemi;
  delete MapFrame;
  delete rect;
  TTF_CloseFont(Sans);
}