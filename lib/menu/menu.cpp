#include "menu.hpp"
#include "../gamemode/gamemode.hpp"


menu::menu() {
    gWindow = nullptr;
    gRenderer = nullptr;
    quit = false;
}

void menu::Init(){
    // 
}

void menu::handleEvents(){
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            // Vérifiez quelle touche a été enfoncée
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true; // Quitte l'application si la touche Échap est enfoncée
                    break;
            }
        }
    }
}

void menu::render(){
    // 
}

void menu::update(){
    // 
}