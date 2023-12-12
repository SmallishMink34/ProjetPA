#include "jeu.hpp"
#include <fstream>

Jeu::Jeu(SDL_Window* window, SDL_Renderer* renderer, Variable* Var) {
  this->gWindow = window;
  this->gRenderer = renderer;

  isLoaded = false;
  this->Var = Var;
}

void Jeu::Init() {
  isLoaded = true;

  Var->ChangeScale(Windows_W / 1280.0);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);

  Monde = new world(this->gRenderer, Var);
  Monde->InitMonde(this->gRenderer);
  this->Monde->previousTime = SDL_GetTicks();
}

void Jeu::Pause(std::string* Gamemode) {
  *Gamemode = "pause";  // Quitte l'application si la touche Échap est enfoncée
  saveScore();
  getBestScore();
}

void Jeu::saveScore() {
    //rajouter 2 conditions : si on ne meurt pas, si tous les ennemis sont morts
    std::ofstream fichierSortie;
    fichierSortie.open(nomFichier, std::ios::app);

    if (fichierSortie.fail()) {
        std::cout << "Erreur à l'ouverture" << std::endl;
    } else {
        fichierSortie << std::to_string(this->Monde->getScore()) << std::endl;
        fichierSortie.close();
    }
}

int Jeu::getBestScore(){
  std::ifstream fichierEntree;
  std::string ligne;
  int mini = 0;

  fichierEntree.open(nomFichier);

  if (fichierEntree.fail()) {
      std::cout << "Erreur à l'ouverture !" << std::endl;
  } else {
      while (getline(fichierEntree, ligne)) {
          if (mini >= std::stoi(ligne) ) {
              mini = std::stoi(ligne);
          }
      }
      fichierEntree.close();
  }
  return mini;
}

void Jeu::unpause() {
  this->Monde->previousTime = SDL_GetTicks();
  this->Var->ChangeScale(Windows_W / 1280.0);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
}

void Jeu::handleEvents(std::string* Gamemode) {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    this->Monde->mouseX = mouseX;
    this->Monde->mouseY = mouseY;
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
      Monde->KeyPressed[4] = true;
    } else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
      Monde->KeyPressed[4] = false;
    }

    if(e.type == SDL_QUIT) {
      quit = true;
    } else if(e.type == SDL_KEYDOWN) {
      // Vérifiez quelle touche a été enfoncée
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
          Pause(Gamemode);  // Quitte l'application si la touche Échap est enfoncée
          break;
        case SDLK_RETURN:
          quit = true;
          break;
        case SDLK_s:
          Monde->KeyPressed[3] = true;
          break;
        case SDLK_z:
          Monde->KeyPressed[2] = true;
          break;
        case SDLK_d:
          Monde->KeyPressed[1] = true;
          break;
        case SDLK_q:
          Monde->KeyPressed[0] = true;
          break;

        case SDLK_SPACE:
          Monde->KeyPressed[2] = true;
          break;
        case SDLK_o:
          Monde->Joueur->IncrementVie(1);
          break;
        case SDLK_l:
          Monde->Joueur->IncrementVie(-1);
          break;
      }
    } else if(e.type == SDL_KEYUP) {
      switch(e.key.keysym.sym) {
        case SDLK_s:
          Monde->KeyPressed[3] = false;
          break;
        case SDLK_z:
          Monde->KeyPressed[2] = false;
          break;
        case SDLK_d:
          Monde->KeyPressed[1] = false;
          break;
        case SDLK_q:
          Monde->KeyPressed[0] = false;
          break;
        case SDLK_SPACE:
          Monde->KeyPressed[2] = false;
          break;
      }
    }
  }
}

void Jeu::render() {
  // Effacer l'écran

  SDL_RenderClear(gRenderer);

  Monde->drawAll(gRenderer);

  // Mettre à jour l'affichage
  SDL_RenderPresent(gRenderer);
}

void Jeu::update() {
  // TODO : Gerer la fin du jeu
  Monde->UpdateAll();
}

Jeu::~Jeu() {
  delete Monde;
  Monde = nullptr;
}