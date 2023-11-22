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
        bool isLoaded;
        float scale;
        int Real_W;
        int Real_H;
        Gamemode();

        virtual void handleEvents(std::string * Gamemode) = 0;
        virtual void Init() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void unpause() = 0;
        ~Gamemode();
};

#endif