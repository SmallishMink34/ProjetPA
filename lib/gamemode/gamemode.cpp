#include "gamemode.hpp"
// Constructor
Gamemode::Gamemode() {
    gWindow = nullptr;
    gRenderer = nullptr;
    quit = false;
    isLoaded = false;
    Var = nullptr;
}



Gamemode::~Gamemode() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit(); 
    SDL_Quit();
}

