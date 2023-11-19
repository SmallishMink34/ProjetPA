#ifndef MENUE_HPP
#define MENUE_HPP
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"
#include "../button/button.hpp"
#include <SDL2/SDL.h>

class menu : public Gamemode {
    public:
        Sprite Image;
        Bouton play;
        Bouton exit;
        SDL_Event evenement;
        menu(SDL_Window* gWindow, SDL_Renderer* gRenderer);
        void Init();
        void handleEvents(std::string* Gamemode);
        void render();
        void update();
};

#endif