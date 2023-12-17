#include "jeu.hpp"

#include <climits>
#include <fstream>

Jeu::Jeu(SDL_Window* window, SDL_Renderer* renderer, Variable* Var) {
  this->gWindow = window;
  this->gRenderer = renderer;

  isLoaded = false;
  this->Var = Var;
  this->gameMusic = nullptr;
  this->Monde = nullptr;
  this->menuSound = nullptr;
}

bool Jeu::Init() {
  isLoaded = true;

  Var->ChangeScale(Windows_W / 1280.0);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);

  Monde = new world(this->gRenderer, Var);
  Monde->InitMonde(this->gRenderer);
  Monde->previousTime = SDL_GetTicks();

  this->menuSound = Mix_LoadWAV("src/music/sounds/menuon.mp3");

  Mix_HaltMusic();
  this->gameMusic = Mix_LoadMUS("src/music/background/game.mp3");
  Mix_PlayMusic(gameMusic, -1);

  // baisse le son de la musique
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
  return 0;
}

void Jeu::Pause(std::string* Gamemode) {
  *Gamemode = "pause";
  Mix_PlayChannel(-1, menuSound, 0);
  Mix_PauseMusic();
}

void Jeu::saveScore() {
  std::cout << "save score : " << this->Monde->getScore() << std::endl;
  std::ofstream fichierSortie;
  fichierSortie.open(nomFichier, std::ios::app);

  if(fichierSortie.fail()) {
    std::cerr << "Erreur à l'ouverture" << std::endl;
  } else {
    fichierSortie << std::to_string(this->Monde->getScore()) << std::endl;
    fichierSortie.close();
  }
}

void Jeu::unpause() {
  this->Monde->previousTime = SDL_GetTicks();
  this->Var->ChangeScale(Windows_W / 1280.0);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
  Mix_ResumeMusic();
}

void Jeu::handleEvents(std::string* Gamemode) {
  if(Monde->EndGame()) {
    if(Monde->Joueur->getVie() > 0) saveScore();
    Var->setScore(Monde->getScore());
    isLoaded = false;
    *Gamemode = "end";
  }

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

int Jeu::update() { return Monde->UpdateAll(); }

Jeu::~Jeu() {
  std::cout << "Destructeur Jeu" << std::endl;
  if(Monde != nullptr) delete Monde;
  if(gameMusic != nullptr) Mix_FreeMusic(gameMusic);
  if(menuSound != nullptr) Mix_FreeChunk(menuSound);

  Monde = nullptr;
}