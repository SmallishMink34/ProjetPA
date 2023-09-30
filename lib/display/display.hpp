#ifndef DefDisplay
#define DefDisplay

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../sprites/sprite.hpp"

class Texture{
    public:
        Texture();
        std::vector<Sprite> Elements;
        void addElements(SDL_Renderer* Renderer,Sprite Element);
        void drawElements(SDL_Renderer * renderer);
        
};


SDL_Texture* loadTexture(SDL_Renderer* Renderer, const std::string& path);

#endif