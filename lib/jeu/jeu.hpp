#ifndef MENU_HPP
#define MENU_HPP

#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"

class Jeu : public Gamemode {
    public:
        Jeu(SDL_Window* gWindow, SDL_Renderer* gRenderer);
        void Init();
        world *Monde = new world(gRenderer);
        void handleEvents(std::string * Gamemode);
        void render();
        void update();
};

#endif