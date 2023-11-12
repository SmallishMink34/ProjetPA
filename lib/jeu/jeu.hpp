#ifndef MENU_HPP
#define MENU_HPP

#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"

class Jeu : public Gamemode {
    public:
        Jeu();
        void Init();
        world *Monde = new world(gRenderer);
        void handleEvents();
        void render();
        void update();
};

#endif