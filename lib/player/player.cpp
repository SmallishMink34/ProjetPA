#include "player.hpp"
#include "../../Constante.hpp"
#include <iostream>

Player::Player(SDL_Renderer* Renderer){
    vie = 3;
    x = 60;
    y = 60;
    dy = 0;
    Realx = 60;
    Realy = 60;
    speed = 5;
    verticalVelocity = 0.0f;
    jumpStrength = 8.0f;
    Jumping = true;
    hasJump = false;
    OnGround = false;
    Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", x, y, 36, 64);
    Image.setSrcRect(24, 180, 36, 64);
    Image.loadImage(Renderer);
}

void Player::InitPlayer(std::vector<tmx::Object> Objects, world* Monde){
    Collisions = Objects;
    std::cout << "Collisions : " << Collisions.size() << std::endl;
    Map = Monde->Map;
    Mondee = Monde;
}


bool Player::isColliding(int x1, int y1, int realx, int realy){
    for (long unsigned int i = 0; i < Collisions.size(); i++){
        for (const auto& collisionObject : Collisions) {
            if (realx + getWidth() > collisionObject.getPosition().x &&
                realx < collisionObject.getPosition().x + collisionObject.getAABB().width &&
                realy+y1 + getHeight() > collisionObject.getPosition().y &&
                realy+y1 < collisionObject.getPosition().y + collisionObject.getAABB().height) 
            {
                if (y1 > 0){
                    AllMove(realx, collisionObject.getPosition().y - getHeight(), true);
                    OnGround = true;
                    y1 = 0;
                }
                else if (y1 < 0){
                    AllMove(realx, collisionObject.getPosition().y + collisionObject.getAABB().height, true);
                    y1 = 0;
                    verticalVelocity = 0;
                }

                if (x1 > 0){
                    AllMove(collisionObject.getPosition().x - getWidth(), realy, true);
                    x1 = 0;
                }
                else if (x1 < 0){
                    AllMove(collisionObject.getPosition().x + collisionObject.getAABB().width, realy, true);
                    x1 = 0;
                }

                return true;
            }
        }
    }

    return false;
}

Player::~Player(){
    
}

void Player::Moveto(int x, int y){

    x = Realx - Mondee->dx;
    y = Realy - Mondee->dy;

    Image.Moveto(x, y);
}

void Player::RealMoveto(int x, int y){
    Realx = x;
    Realy = y;
}

void Player::Move(int x1, int y1){ // Pas les coordonnées, seulement le vecteur de déplacements
    printf("x1 : %d, y1 : %d\n", x1, y1);
    if (y1 > 0 || OnGround == true){
        if (!isColliding(0, y1, Realx, Realy)){
            OnGround = false;
        }
    }

    isColliding(x1, y1, Realx, Realy);
    AllMove(x1, y1, false);

}

void Player::AllMove(int x1, int y1, bool Teleport){
    if (!Teleport){
        Moveto(x + x1, y + y1);
        RealMoveto(Realx + x1, Realy + y1);
    }else{
        Moveto(x1, y1);
        RealMoveto(x1, y1);
    }
}

void Player::FixCamera(){
    if (x > Map->getMapWidth() - Real_W/2){
        int nombre = Map->getMapWidth()-Real_W;
        x = x - nombre;
    }
    if (y > Map->getMapHeight() - Real_H/2){
        int nombre = Map->getMapHeight()-Real_H;
        y = y - nombre;
    }
    Image.Moveto(x, y);
}

void Player::applyGravity(float deltaTime) {
    dy = 0;
    verticalVelocity += Gravity;
    dy += verticalVelocity;

    if (isOnGround()){ 
        dy = 0;
        verticalVelocity = 0;
        setIsJumping(false);
        if (hasJump){ // Seulement si il est sur le sol
            verticalVelocity = -jumpStrength;; 
        }
    }
    
    if (!isJumping()) hasJump = false;
    Move(0, dy * deltaTime); 
}

int Player::getX(){
    return Realx;
}

int Player::getY(){
    return Realy;
}

std::string Player::GetName(){
    return Nom;
}

void Player::SetName(const std::string Name){
    Nom = Name;
}

std::string Player::toString(){
    return ("X : " + std::to_string(x) + " Y : " + std::to_string(y));
}

int Player::getWidth(){
    return Image.getWidth();
}

int Player::getHeight(){
    return Image.getHeight();
}


bool Player::isOnGround(){
    return OnGround;
}

void Player::jump() {
    if (isOnGround()) {
        hasJump = true;
    }
}

float Player::getVerticalVelocity(){
    return verticalVelocity;
}

bool Player::isJumping(){
    return Jumping;
}

void Player::setIsJumping(bool Jump){
    Jumping = Jump; 

}