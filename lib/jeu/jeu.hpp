#ifndef MENU_HPP
#define MENU_HPP

#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"


class Jeu : public Gamemode {
    public:
        Jeu(SDL_Window* gWindow, SDL_Renderer* gRenderer);
        void Init();
        void Pause(std::string* Gamemode);
        world *Monde = new world(gRenderer, Real_W, Real_H);
        void handleEvents(std::string * Gamemode);
        void render();
        void update();
        void unpause();
        int Real_W;
        int Real_H;
};

#endif