#include "gamemode.hpp"
#include "../../Constante.hpp"
// Constructor
Gamemode::Gamemode() {
    gWindow = nullptr;
    gRenderer = nullptr;
    quit = false;
    isLoaded = false;
    scale = 1.0f;
    Real_W =  Windows_W/scale;
    Real_H =  Windows_H/scale;
}



Gamemode::~Gamemode() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit(); 
    SDL_Quit();
}

