#include "end.hpp"

#include <SDL2/SDL_ttf.h>

#include <fstream>

#include "../gamemode/gamemode.hpp"
#include "../utility/utility.hpp"

END::END(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var) {
  this->gWindow = gWindow;
  this->gRenderer = gRenderer;
  quit = false;
  isLoaded = false;
  this->Var = Var;
  menu = false;
  this->Image = new Sprite("src/Images/bg.jpg", 0, 0, Var->Real_W, Var->Real_H);
  this->exit = new Bouton(gRenderer, "src/Images/exit.png", 3 * Var->Real_W / 8, 3 * Var->Real_H / 4, 192, 96, true);
  this->main_menu = new Bouton(gRenderer, "src/Images/menu.png", 5 * Var->Real_W / 8, 3 * Var->Real_H / 4, 192, 96, true);
  this->Sans = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  this->score = Var->getScore();
  this->scoredialg = new texte(gRenderer, "Score : ", LightBlue, {Var->Real_W / 2, Var->Real_H / 3, 50, 100}, true, true);
  this->scoreText = new texte(gRenderer, std::to_string(score), LightBlue, {Var->Real_W / 2, 5 * Var->Real_H / 11, 100, 100}, true, true);
  this->info = new texte(gRenderer, "Your score will be saved only if you win", LightBlue, {Var->Real_W / 2, 9 * (Var->Real_H / 10), 18, 25}, true, true);
  this->win = new texte(gRenderer, "WIN", LightBlue, {Var->Real_W / 2, Var->Real_H / 8, 100, 200}, true, true);
}

int END::Init() {
  this->score = Var->getScore();
  isLoaded = true;
  Var->ChangeScale(1);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);

  Image->loadImage(gRenderer);

  // bouton exit

  this->exit->setSurface(0, 256, 512, 256);
  this->exit->gererFin(&evenement, gRenderer, &quit);

  // bouton menu
  this->main_menu->setSurface(0, 0, 512, 256);
  this->main_menu->gererFin(&evenement, gRenderer, &quit);

  // TODO : Afficher meilleur score
  if(!Var->win) {
    this->win->setText("LOSE", Var->Real_W / 2, Var->Real_H / 8, 100, 200);
    this->win->setColor(LightRed);
  }

  this->scoreText->setText(std::to_string(score), Var->Real_W / 2, 5 * Var->Real_H / 11, 100, 100);
  return 0;
}
void END::handleEvents(std::string* Gamemode) {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    exit->gererFin(&e, this->gRenderer, &quit);
    main_menu->gererMenu(&e, this->gRenderer, &menu);
    if(menu) {
      menu = false;
      *Gamemode = "menu";
    }
    if(e.type == SDL_QUIT) {
      quit = true;
    } else if(e.type == SDL_KEYDOWN) {
      // Vérifiez quelle touche a été enfoncée
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = true;  // Quitte l'application si la touche Échap est enfoncée
          var = false;
          break;
      }
    }

    // Appeler la fonction de gestion des événements du bouton
  }
}

void END::render() {
  // Efface le renderer
  SDL_RenderClear(gRenderer);
  Image->selfDraw(gRenderer);
  exit->selfDraw(gRenderer);
  main_menu->selfDraw(gRenderer);
  scoredialg->draw(gRenderer);
  scoreText->draw(gRenderer);
  info->draw(gRenderer);
  win->draw(gRenderer);

  SDL_RenderPresent(gRenderer);
}

int END::update() { return 0; }

void END::unpause() {
  Var->ChangeScale(1);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
}

END::~END() {
  delete Image;
  delete main_menu;
  delete exit;
  delete scoredialg;
  delete scoreText;
  delete info;
  delete win;
  TTF_CloseFont(Sans);
}