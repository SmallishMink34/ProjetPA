
#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"
#include "../../Constante.hpp"
#include "jeu.hpp"

Jeu::Jeu(SDL_Window* gWindow, SDL_Renderer* gRenderer) {
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    quit = false;
    isLoaded = false;

    scale = Windows_W/1280.0-0.02;
    Real_W =  Windows_W/scale;
    Real_H =  Windows_H/scale;
}

void Jeu::Init(){
    isLoaded = true;

    SDL_RenderSetScale(this->gRenderer, scale, scale); // Faire un zoom dans la fenetre
    SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
    Monde = new world(gRenderer, Real_W, Real_H);
    
    Monde->InitMonde(gRenderer);
    
}

void Jeu::Pause(std::string* Gamemode)
{
    
    *Gamemode = "pause"; // Quitte l'application si la touche Échap est enfoncée

}

void Jeu::unpause()
{
    this->Monde->previousTime = SDL_GetTicks();
}

void Jeu::handleEvents(std::string * Gamemode) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            // Vérifiez quelle touche a été enfoncée
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    Pause(Gamemode); // Quitte l'application si la touche Échap est enfoncée
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

void Jeu::update() {
    Monde->UpdateAll();
}