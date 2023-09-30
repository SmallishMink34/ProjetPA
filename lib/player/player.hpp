#ifndef DefPlayer
#define DefPlayer
#include <iostream>
#include "../sprites/sprite.hpp"

class Player{
    public:
        // Constructeur
        Player(SDL_Renderer* Renderer);

        // Variables
        int vie;
        Sprite Image;
        int x;
        int y;
        int speed;

        // Fonctions
        std::string GetName();
        void SetName(const std::string Name);
        void Moveto(int x, int y);
        void Move(int x, int y);
        int getX();
        int getY();
        ~Player();

    private:
        std::string Nom;
};

#endif