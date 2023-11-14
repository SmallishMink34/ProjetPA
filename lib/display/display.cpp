#include "display.hpp"
#include <SDL2/SDL_image.h>

Texture::Texture(){
}


void Texture::addElements(SDL_Renderer* Renderer,Sprite Element){
    this->Elements.push_back(Element);
    SDL_Texture* texture = loadTexture(Renderer, this->Elements[this->Elements.size()-1].Getlink());
    if (texture == nullptr) {
        std::cerr << "Échec du chargement de l'image." << std::endl;
    }
    this->Elements[this->Elements.size()-1].SetImage(texture);
}

void Texture::drawElements(SDL_Renderer * renderer){
    for (long unsigned i = 0; i<this->Elements.size(); i++){
        this->Elements[i].selfDraw(renderer);
    }
}

// Fonction pour charger une image
SDL_Texture* loadTexture(SDL_Renderer *Renderer,const std::string& path) { // Reference a un string sans le modifier
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Impossible de charger l'image " << path << " : " << IMG_GetError() << std::endl;
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
    if (newTexture == nullptr) {
        std::cerr << "Impossible de créer une texture à partir de " << path << " : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);

    return newTexture;
}