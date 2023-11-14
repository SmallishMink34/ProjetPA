#include "gamemode.hpp"
// Constructor
Gamemode::Gamemode() {
    gWindow = nullptr;
    gRenderer = nullptr;
    quit = false;
    phase = 0;
}



Gamemode::~Gamemode() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit(); 
    SDL_Quit();
}

