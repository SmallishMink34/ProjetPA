#ifndef DefPlayer
#define DefPlayer
#include <iostream>
#include "../world/world.hpp"
#include "../sprites/sprite.hpp"
#include "../maps/maps.hpp"

class world;
class Player{
    public:
        // Constructeur
        Player(SDL_Renderer* Renderer);

        // Variables
        int vie;
        Sprite Image;
        int speed;
        std::vector<tmx::Object> Collisions;

        // Fonctions
        std::string GetName();
        void SetName(const std::string Name);
        void Moveto();
        void RealMoveto(int x, int y);
        void Move(int x, int y);
        int getWidth();
        int getHeight();

        tmx::Object* isColliding(int x1, int y1, int realx, int realy);
        int getRX();
        int getRY();
        int getX();
        int getY();

        std::string toString();
        void InitPlayer(std::vector<tmx::Object> Objects, world* Monde);
        void FixCamera();
        void AllMove(int x1, int y1, bool Teleport);
        bool isOnGround();
        float getVerticalVelocity();
        void jump();
        bool isJumping();
        void setIsJumping(bool Jump);
        void applyGravity(float deltaTime);
        ~Player();

    private:
        std::string Nom;
        int x;
        int y; 
        float dy;
        int Realx;
        int Realy;

        int oldRealx;
        int oldRealy;
        bool OnGround;
        bool Jumping;
        bool hasJump;
        float verticalVelocity;
        float jumpStrength;
        float jumpTime;
        level* Map; 
        world* Mondee;
};



#endif