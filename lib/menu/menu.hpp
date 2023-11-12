#ifndef MENUE_HPP
#define MENUE_HPP
#include "../gamemode/gamemode.hpp"

class menu : public Gamemode {
    public:
        menu();
        void Init();
        void handleEvents();
        void render();
        void update();
};

#endif