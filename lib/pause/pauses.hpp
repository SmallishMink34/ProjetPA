#ifndef pause_HPP
#define pause_HPP
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"
#include "../button/button.hpp"
#include <SDL2/SDL.h>

class Mpause : public Gamemode {
    public:
        Sprite Image;
        Bouton play;
        Bouton exit;
        SDL_Event evenement;
        Mpause(SDL_Window* gWindow, SDL_Renderer* gRenderer);
        void Init();
        void handleEvents(std::string* Gamemode);
        void render();
        void update();
        void unpause();
        int Real_W;
        int Real_H;
};

#endif