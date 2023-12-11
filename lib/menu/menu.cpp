#include "menu.hpp"

menu::menu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var) {
  this->gWindow = gWindow;
  this->gRenderer = gRenderer;
  quit = false;
  isLoaded = false;
  var = false;
  this->Var = Var;
  this->Image = new Sprite("src/Images/bg.jpg", 0, 0, Var->Real_W, Var->Real_H);
  this->titre = new Sprite("src/Images/titre.png", (int)(Var->Real_W / 3), (int)(Var->Real_H / 10), (int)(Var->Real_W / 3), (int)(Var->Real_H / 3));
  this->play = new Bouton(gRenderer, "src/Images/play.png", Var->Real_W / 3.6, Var->Real_H / 1.7, 256, 128);
  this->exit = new Bouton(gRenderer, "src/Images/exit.png", Var->Real_W / 1.66, Var->Real_H / 1.7, 256, 128);
}

void menu::Init() {
  isLoaded = true;
  Var->ChangeScale(1);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);

  Image->loadImage(gRenderer);
  titre->loadImage(gRenderer);

  // bouton play

  this->play->setSurface(0, 0, 512, 256);

  this->play->gererPlay(&evenement, gRenderer, &var);

  // bouton exit

  this->exit->setSurface(0, 256, 512, 256);
  this->exit->gererFin(&evenement, gRenderer, &quit);
}

void menu::handleEvents(std::string* Gamemode) {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    exit->gererFin(&e, this->gRenderer, &quit);

    play->gererPlay(&e, this->gRenderer, &var);

    if(var) {
      *Gamemode = "jeu";
    }
    if(e.type == SDL_QUIT) {
      quit = true;
    } else if(e.type == SDL_KEYDOWN) {
      // Vérifiez quelle touche a été enfoncée
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = true;  // Quitte l'application si la touche Échap est enfoncée

          break;
      }
    }

    // Appeler la fonction de gestion des événements du bouton
  }
}

void menu::render() {
  // Efface le renderer
  SDL_RenderClear(gRenderer);
  Image->selfDraw(gRenderer);
  titre->selfDraw(gRenderer);

  exit->selfDraw(gRenderer);

  play->selfDraw(gRenderer);
  // Met à jour le renderer
  SDL_RenderPresent(gRenderer);
}

void menu::update() {}

void menu::unpause() {}

menu::~menu() {
  if(isLoaded) {
    delete Image;
    delete titre;
    delete play;
    delete exit;
  }
}