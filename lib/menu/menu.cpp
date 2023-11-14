#include "menu.hpp"
#include "../gamemode/gamemode.hpp"
#include "../../Constante.hpp"


menu::menu(SDL_Window* gWindow, SDL_Renderer* gRenderer) {
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    
    quit = false;
}

void menu::Init(){
    Image = Sprite("src/Images/bg.png", 0, 0, Real_W, Real_H);
    Image.loadImage(gRenderer);
}

void menu::handleEvents(std::string* Gamemode){
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
                case SDLK_RETURN:

                    *Gamemode = "jeu";
                    break;
                case SDLK_p:
                    printf("%d\n", phase);
            }
        }
    }
}


void menu::render(){
    // Efface le renderer
    SDL_RenderClear(gRenderer);
    Image.selfDraw(gRenderer);
    // Met à jour le renderer
    SDL_RenderPresent(gRenderer);
    
}

void menu::update(){

}