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
  this->exit = new Bouton(gRenderer, "src/Images/exit.png", Var->Real_W / 1.66, Var->Real_H / 1.7, 192, 96);
  this->main_menu = new Bouton(gRenderer, "src/Images/menu.png",  Var->Real_W / 4.6, Var->Real_H / 1.7, 192, 96);
  this->TextureMessage = nullptr;
  this->TextureSeed = nullptr;
  this->Sans = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  this->score = Var->getScore();
  this->scoredialg = new texte(gRenderer, "Score : ", {0, 191, 255}, {Var->Real_W / 2, Var->Real_H / 3, 50, 100}, true, true);
  this->scoreText = new texte(gRenderer, std::to_string(score), {0, 191, 255}, {Var->Real_W / 2, Var->Real_H / 2 - 50, 100, 100}, true, true);
  this->info = new texte(gRenderer, "Your score will be saved only if you win", {0, 191, 255},
                         {(Var->Real_W / 3), 9 * (Var->Real_H / 10), 18, 25}, true, false);
}

void END::Init() {
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

  SDL_Color Blue = {0, 191, 255};

  this->scoreText->setText(std::to_string(score));
  std::cout << "Tu as fini la partie avec un score de " << Var->getScore() << std::endl;
}
void END::handleEvents(std::string* Gamemode) {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    // TODO : Son bouton
    // TODO : Bouton Mute
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
  SDL_RenderCopy(gRenderer, TextureSeed, NULL, &Seed_rect);
  SDL_RenderCopy(gRenderer, TextureMessage, NULL, &Message_rect);
  scoredialg->draw(gRenderer);
  scoreText->draw(gRenderer);
  info->draw(gRenderer);

  SDL_RenderPresent(gRenderer);
}

void END::update() {}

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
  if(TextureMessage != nullptr) {
    SDL_DestroyTexture(TextureMessage);
  }

  if(TextureSeed != nullptr) {
    SDL_DestroyTexture(TextureSeed);
  }
  TTF_CloseFont(Sans);
}