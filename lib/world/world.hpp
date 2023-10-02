#ifndef DefWorld
#define DefWorld

#include "../player/player.hpp"
#include "../display/display.hpp"
#include "../maps/maps.hpp"

class world
{
    public:
        // Constucteur
        world(SDL_Renderer* Renderer);
        // Variables
        Player* Joueur;
        Texture AllElements;
        level* Map;
        bool KeyPressed[4] = {false, false, false, false}; // 0 = left, 1 = right, 2 = up, 3 = down

        int dx; // Décalage X de la map par rapport au personnage.
        int dy;

        Uint32 currentTime;
        double deltaTime;
        Uint32 previousTime;
        // Fonctions
        void InitMonde(SDL_Renderer* Renderer);
        void drawAll(SDL_Renderer* Renderer);
        void movePlayer();
        void UpdateAll();
        void moveCamera();
        
        
};  


#endif