#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Constante.hpp"
#include "lib/world/world.hpp"
#include "lib/display/display.hpp"
#include "lib/jeu/jeu.hpp"
#include "lib/menu/menu.hpp"
#include "lib/pause/pauses.hpp"
#include <map>

SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

// Fonction pour initialiser SDL
bool initSDL(Gamemode* Monde) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return false;
    }
    
    gWindow = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Windows_W, Windows_H, SDL_WINDOW_FULLSCREEN);
    if (gWindow== nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        return false;
    }
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        std::cerr << "Erreur lors de la création du rendu : " << SDL_GetError() << std::endl;
        return false;
    }
    
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(Monde->gWindow);

    IMG_Quit(); 
    SDL_Quit();
}

int main(int argc, char* args[]) {
    std::map<std::string, Gamemode*> Gamemodes;

    std::string currentGamemode = "menu";
    std::string oldGamemode = currentGamemode;
    
    if (!init(Gamemodes[currentGamemode])){
        return 1;
    }
    

    Gamemodes["jeu"] = new Jeu(gWindow, gRenderer);
    Gamemodes["menu"] = new menu(gWindow, gRenderer);
    Gamemodes["pause"] = new Mpause(gWindow, gRenderer);    
    
    Gamemodes[currentGamemode]->Init();
    Uint32 targetFPS = fps;
    Uint32 frameDelay = 1000 / targetFPS;
    Uint32 frameStart, frameTime;
    
    
    
    while (!Gamemodes[currentGamemode]->quit) {
        
        frameStart = SDL_GetTicks();
        
        oldGamemode = currentGamemode;
        Gamemodes[currentGamemode]->handleEvents(&currentGamemode);
        if (currentGamemode != oldGamemode && !Gamemodes[currentGamemode]->isLoaded){
            Gamemodes[currentGamemode]->Init();
        }else if (currentGamemode != oldGamemode && Gamemodes[currentGamemode]->isLoaded){
            // Un pause
            Gamemodes[currentGamemode]->unpause();
        }
        
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
