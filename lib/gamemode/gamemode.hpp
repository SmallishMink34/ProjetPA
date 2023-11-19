#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../world/world.hpp"

class Gamemode {
    public:
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        bool quit;
        bool var;
        
        Gamemode();

        virtual void handleEvents(std::string * Gamemode) = 0;
        virtual void Init() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        ~Gamemode();
};

#endif