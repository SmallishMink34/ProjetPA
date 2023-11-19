#include "menu.hpp"
#include "../gamemode/gamemode.hpp"
#include "../../Constante.hpp"
//#include "../button/button.cpp"


menu::menu(SDL_Window* gWindow, SDL_Renderer* gRenderer){
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    quit = false;
    var = false;
    this->Image = Sprite("src/Images/bg.jpg", 0, 0, Real_W, Real_H);
    Image.loadImage(gRenderer);

    //bouton exit
    this->exit = Bouton(gRenderer, "src/Images/exit.png", Real_W/2-128, Real_H/1.67, 256, 128);
    this->exit.setSurface(0, 256, 512, 256);
    this->exit.gererFin(&evenement, gRenderer, &quit);

    //bouton play
    this->play = Bouton(gRenderer, "src/Images/play.png", Real_W/2-128, Real_H/3, 256, 128);
    this->play.setSurface(0, 0, 512, 256);
    this->play.gererPlay(&evenement, gRenderer, &var);
}

void menu::Init() {
    //
}

void menu::handleEvents(std::string* Gamemode) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        exit.gererFin(&e, this->gRenderer, &quit);
        play.gererPlay(&e, this->gRenderer, &var);
        if(var){
            *Gamemode = "jeu";
        }
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            // Vérifiez quelle touche a été enfoncée
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true; // Quitte l'application si la touche Échap est enfoncée
                    break;
                case SDLK_RETURN:
                    *Gamemode = "jeu";
                    break;
            }
        }

        // Appeler la fonction de gestion des événements du bouton
        
    }
}

void menu::render() {
    // Efface le renderer
    SDL_RenderClear(gRenderer);
    Image.selfDraw(gRenderer);
    exit.selfDraw(gRenderer);
    play.selfDraw(gRenderer);
    // Met à jour le renderer
    SDL_RenderPresent(gRenderer);
}

void menu::update() {
    // Ajoutez ici toute mise à jour nécessaire

}
