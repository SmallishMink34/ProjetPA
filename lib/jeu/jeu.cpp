
#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"
#include "jeu.hpp"

Jeu::Jeu() {
    gWindow = nullptr;
    gRenderer = nullptr;
    quit = false;
}

void Jeu::Init(){
    Monde = new world(gRenderer);
    Monde->InitMonde(gRenderer);
}

void Jeu::handleEvents() {
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

void Jeu::render() {
    // Effacer l'écran
    SDL_RenderClear(gRenderer);

    Monde->drawAll(gRenderer);
    
    // Mettre à jour l'affichage
    SDL_RenderPresent(gRenderer);
}

void Jeu::update() {
    Monde->UpdateAll();
}