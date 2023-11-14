#ifndef MENUE_HPP
#define MENUE_HPP
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"

class menu : public Gamemode {
    public:
        menu(SDL_Window* gWindow, SDL_Renderer* gRenderer);
        void Init();
        void handleEvents(std::string* Gamemode);
        void render();
        void update();
        
        Sprite Image;
};

#endif