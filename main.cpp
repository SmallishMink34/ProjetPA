#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <map>

#include "lib/Variables/variables.hpp"
#include "lib/display/display.hpp"
#include "lib/end/end.hpp"
#include "lib/jeu/jeu.hpp"
#include "lib/menu/menu.hpp"
#include "lib/pause/pauses.hpp"
#include "lib/world/world.hpp"

SDL_Renderer *gRenderer = nullptr;
SDL_Window *gWindow = nullptr;

// Fonction pour initialiser SDL
bool initSDL() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
    return false;
  }

  gWindow = SDL_CreateWindow("Mystic Depths", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Windows_W, Windows_H, SDL_WINDOW_BORDERLESS);
  if(gWindow == nullptr) {
    std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
    return false;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(gRenderer == nullptr) {
    std::cerr << "Erreur lors de la création du rendu : " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    std::cerr << "SDL_image n'a pas pu être initialisé : " << IMG_GetError() << std::endl;
    return false;
  }

  if(TTF_Init() == -1) {
    std::cerr << "SDL_ttf n'a pas pu être initialisé : " << TTF_GetError() << std::endl;
    return false;
  }

  if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
    std::cerr << "SDL_mixer n'a pas pu être initialisé : " << Mix_GetError() << std::endl;
    return false;
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    // Gestion de l'erreur lors de l'ouverture de l'audio
    SDL_Quit();
    return -1;
  }

  return true;
}

bool init() {
  if(!initSDL()) {
    std::cerr << "Échec de l'initialisation de SDL." << std::endl;
    return false;
  }

  return true;
}

void FreeGamemodes(std::map<std::string, Gamemode *> *Gamemodes, Variable *Var) {
  delete(*Gamemodes)["jeu"];
  delete(*Gamemodes)["menu"];
  delete(*Gamemodes)["pause"];
  delete(*Gamemodes)["end"];

  delete Var;
}

// Fonction pour libérer les ressources et quitter SDL
void closeSDL() {
  if(gRenderer != nullptr) SDL_DestroyRenderer(gRenderer);
  if(gWindow != nullptr) SDL_DestroyWindow(gWindow);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

int main(int argc, char *args[]) {
  std::map<std::string, Gamemode *> Gamemodes;

  std::string currentGamemode = "menu";
  std::string oldGamemode = currentGamemode;
  Variable *Var = new Variable();

  if(!init()) {
    return 1;
  }

  Gamemodes["jeu"] = new Jeu(gWindow, gRenderer, Var);
  Gamemodes["menu"] = new menu(gWindow, gRenderer, Var);
  Gamemodes["pause"] = new Mpause(gWindow, gRenderer, Var);
  Gamemodes["end"] = new END(gWindow, gRenderer, Var);

  Gamemodes[currentGamemode]->Init();

  Uint32 targetFPS = Var->fps;
  Uint32 frameDelay = 1000 / targetFPS;
  Uint32 frameStart, frameTime;

  while(!Gamemodes[currentGamemode]->quit) {
    frameStart = SDL_GetTicks();

    oldGamemode = currentGamemode;

    Gamemodes[currentGamemode]->handleEvents(&currentGamemode);

    if(currentGamemode != oldGamemode && Gamemodes[currentGamemode]->isLoaded && currentGamemode == "jeu" && oldGamemode == "menu") {
      delete Gamemodes["jeu"];
      std::cout << "delete jeu" << std::endl;
      Gamemodes["jeu"] = new Jeu(gWindow, gRenderer, Var);
      Gamemodes["jeu"]->isLoaded = false;
    }

    if(currentGamemode != oldGamemode && !Gamemodes[currentGamemode]->isLoaded) {
      if(Gamemodes[currentGamemode]->Init() == -1) {
        std::cerr << "Erreur lors de l'initialisation du mode de jeu " << currentGamemode << std::endl;
        return -1;
      }
    } else if(currentGamemode != oldGamemode && Gamemodes[currentGamemode]->isLoaded) {
      Gamemodes[currentGamemode]->unpause();
    }

    if(Gamemodes[currentGamemode]->update() == -1) {
      std::cerr << "Erreur lors de la mise à jour du mode de jeu " << currentGamemode << std::endl;
      return -1;
    }

    Gamemodes[currentGamemode]->render();

    frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  FreeGamemodes(&Gamemodes, Var);

  closeSDL();

  return 0;
}
