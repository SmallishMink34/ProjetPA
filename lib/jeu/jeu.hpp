#ifndef MENU_HPP
#define MENU_HPP

#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"
#include "../Variables/variables.hpp"


class Jeu : public Gamemode {
    public:
        Jeu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);
        void Init();
        void Pause(std::string* Gamemode);
        world *Monde = new world(gRenderer, Var);
        void handleEvents(std::string * Gamemode);
        void render();
        void update();
        void unpause();
};

#endif