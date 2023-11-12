#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Constante.hpp"
#include "lib/world/world.hpp"
#include "lib/display/display.hpp"
#include "lib/jeu/jeu.hpp"
#include "lib/menu/menu.hpp"
#include <map>

// Fonction pour initialiser SDL
bool initSDL(Gamemode* Monde) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return false;
    }

    Monde->gWindow = SDL_CreateWindow("Exemple SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Windows_W, Windows_H, SDL_WINDOW_FULLSCREEN);
    if (Monde->gWindow == nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        return false;
    }

    Monde->gRenderer = SDL_CreateRenderer(Monde->gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Monde->gRenderer == nullptr) {
        std::cerr << "Erreur lors de la création du rendu : " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(Monde->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image n'a pas pu être initialisé : " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool init(Gamemode *Monde){
    if (!initSDL(Monde)) {
        std::cerr << "Échec de l'initialisation de SDL." << std::endl;
        return false;
    }

    return true;
}

// Fonction pour gérer les événements


// Fonction pour libérer les ressources et quitter SDL
void closeSDL(Gamemode* Monde) {
    SDL_DestroyRenderer(Monde->gRenderer);
    SDL_DestroyWindow(Monde->gWindow);

    IMG_Quit(); 
    SDL_Quit();
}

int main(int argc, char* args[]) {
    std::map<std::string, Gamemode*> Gamemodes;

    Gamemodes["jeu"] = new Jeu();
    Gamemodes["menu"] = new menu();

    std::string currentGamemode = "menu";
    
    if (!init(Gamemodes[currentGamemode])){
        return 1;
    }
    Gamemodes[currentGamemode]->Init();
    Uint32 targetFPS = fps;
    Uint32 frameDelay = 1000 / targetFPS;
    Uint32 frameStart, frameTime;

    SDL_RenderSetScale(Gamemodes[currentGamemode]->gRenderer, scale, scale); // Faire un zoom dans la fenetre
    SDL_SetRenderDrawBlendMode(Gamemodes[currentGamemode]->gRenderer, SDL_BLENDMODE_BLEND);

    while (!Gamemodes[currentGamemode]->quit) {
        frameStart = SDL_GetTicks();

        Gamemodes[currentGamemode]->handleEvents();
        Gamemodes[currentGamemode]->update();
        
        Gamemodes[currentGamemode]->render();
        

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    closeSDL(Gamemodes[currentGamemode]);

    return 0;
}
