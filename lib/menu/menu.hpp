#ifndef MENUE_HPP
#define MENUE_HPP
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"
#include "../button/button.hpp"
#include <SDL2/SDL.h>

class menu : public Gamemode {
    public:
        Sprite Image;
        Sprite titre;
        Bouton play;
        Bouton exit;
        SDL_Event evenement;
        menu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);
        void Init();
        void handleEvents(std::string* Gamemode);
        void render();
        void update();
        void unpause();
        int Real_W;
        int Real_H;
        bool var;
};

#endif