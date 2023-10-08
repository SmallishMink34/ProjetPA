#ifndef DefPlayer
#define DefPlayer
#include <iostream>
#include "../sprites/sprite.hpp"
#include "../maps/maps.hpp"

class Player{
    public:
        // Constructeur
        Player(SDL_Renderer* Renderer, level* Map);

        // Variables
        int vie;
        Sprite Image;
        int speed;
        std::vector<tmx::Object> Collisions;

        // Fonctions
        std::string GetName();
        void SetName(const std::string Name);
        void Moveto(int x, int y);
        void RealMoveto(int x, int y);
        void Move(int x, int y);
        int getWidth();
        int getHeight();

        bool isColliding(int x1, int y1);
        int getX();
        int getY();
        std::string toString();
        void InitPlayer(std::vector<tmx::Object> Objects);
        void FixCamera();
        ~Player();

    private:
        std::string Nom;
        int x;
        int y;
        int Realx;
        int Realy;
        level* Map; 
};

#endif