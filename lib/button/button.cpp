// button.cpp
#include "button.hpp"
#include <SDL2/SDL.h>

Bouton::Bouton(){
    this->etat = 0;
    this->rect = new SDL_Rect();
    this->rect->x = 0;
    this->rect->y = 0;
    this->rect->w = 0;
    this->rect->h = 0;
}

Bouton::Bouton(SDL_Renderer* Renderer, const char* lien, int x, int y, int w, int h){
    this->etat = 0;
    this->rect = new SDL_Rect();
    this->rect->x = x;
    this->rect->y = y;
    this->rect->w = w;
    this->rect->h = h;

    this->image = new Sprite(lien, x, y, w, h);
    
    this->image->loadImage(Renderer);
}

void Bouton::setSurface(int x, int y,int w,int h){
    this->image->setSrcRect(x, y, w, h);
}

SDL_Rect* Bouton::getRect(){
    return this->rect;
}

int Bouton::getX(){
    return this->getRect()->x;
}

int Bouton::getY(){
    return this->getRect()->y;
}


int Bouton::getWidth(){
    return this->getRect()->w;
}

int Bouton::getHeight(){
    return this->getRect()->h;
}

bool Bouton::isColliding(int mouseX, int mouseY){
    if (mouseX >= this->getX() && mouseX <= this->getX()+ this->getWidth() &&
        mouseY >= this->getY() && mouseY <= this->getY() + this->getHeight()) {
            return true;
    }
    return false;
}

void Bouton::gererFin(SDL_Event* evenement, SDL_Renderer* rendu, bool* quit) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (isColliding(mouseX, mouseY)) {
        if (evenement->type == SDL_MOUSEMOTION) {
            this->setSurface(0, 0, 512, 256);
        } else if (evenement->type == SDL_MOUSEBUTTONDOWN && evenement->button.button == SDL_BUTTON_LEFT) {
            printf("fin\n");
            *quit = true;
        }
    }else{
            this->setSurface(0, 256, 512, 256);
    }
}

void Bouton::gererPlay(SDL_Event* evenement, SDL_Renderer* rendu, bool* var) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (isColliding(mouseX, mouseY)) {
        if (evenement->type == SDL_MOUSEMOTION) {
            this->setSurface(0, 0, 512, 256);
        } else if (evenement->type == SDL_MOUSEBUTTONDOWN && evenement->button.button == SDL_BUTTON_LEFT) {
            *var = true;
        }
    }else{
            this->setSurface(0, 256, 512, 256);
    }
}

void Bouton::gererMenu(SDL_Event* evenement, SDL_Renderer* rendu, bool* menu) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (isColliding(mouseX, mouseY)) {
        if (evenement->type == SDL_MOUSEMOTION) {
            this->setSurface(0, 0, 512, 256);
        } else if (evenement->type == SDL_MOUSEBUTTONDOWN && evenement->button.button == SDL_BUTTON_LEFT) {
            *menu = true;
        }
    }else{
            this->setSurface(0, 256, 512, 256);
    }
}


void Bouton::selfDraw(SDL_Renderer * gRenderer){
    image->selfDraw(gRenderer);
}