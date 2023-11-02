#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Constante.hpp"
#include "lib/world/world.hpp"
#include "lib/display/display.hpp"


// Fenêtre et rendu
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
// Gestion des événements
bool quit = false;

// Fonction pour initialiser SDL
bool initSDL() { 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Exemple SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Windows_W, Windows_H, SDL_WINDOW_FULLSCREEN);
    if (gWindow == nullptr) {
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

bool init(){
    if (!initSDL()) {
        std::cerr << "Échec de l'initialisation de SDL." << std::endl;
        return false;
    }

    return true;
}

// Fonction pour gérer les événements
void handleEvents(world* Monde) {
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
                
                case SDLK_p: 
                    std::cout << "RealX : " << Monde->Joueur->getRX() << " RealY : " << Monde->Joueur->getRY() << std::endl;
                    std::cout << Monde->Joueur->toString() << std::endl;
                    break;
            }
        }else if(e.type == SDL_KEYUP){
            switch (e.key.keysym.sym) {
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
            }
        }
    }
}

// Fonction pour libérer les ressources et quitter SDL
void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    IMG_Quit(); 
    SDL_Quit();
}

int main(int argc, char* args[]) {
    
    if ( !init()){
        return 1;
    } 
    Uint32 targetFPS = fps;
    Uint32 frameDelay = 1000 / targetFPS;
    Uint32 frameStart, frameTime;
    
    world *Monde = new world(gRenderer);
    
    Monde->InitMonde(gRenderer);
    SDL_RenderSetScale(gRenderer, scale, scale); // Faire un zoom dans la fenetre
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    while (!quit) {
        frameStart = SDL_GetTicks();
        // Effacer l'écran
        SDL_RenderClear(gRenderer);

        handleEvents(Monde);
        Monde->UpdateAll();
        
        Monde->drawAll(gRenderer);
        
        // Mettre à jour l'affichage
        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    closeSDL();

    return 0;
}
