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
    jumpStrength = 20.0f;
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
            if (x1 + getWidth() > collisionObject.getPosition().x &&
                x1 < collisionObject.getPosition().x + collisionObject.getAABB().width &&
                y1 + getHeight() > collisionObject.getPosition().y &&
                y1 < collisionObject.getPosition().y + collisionObject.getAABB().height) {
                    return false;
            }
        }
    }

    return false;
}

bool Player::isCollidingBottom(int x1, int y1, int realx, int realy){
    for (long unsigned int i = 0; i < Collisions.size(); i++){
        for (const auto& collisionObject : Collisions) {
            if (y1 + getHeight() > collisionObject.getPosition().y &&
                y1 < collisionObject.getPosition().y + collisionObject.getAABB().height) {
                    return false;
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
    if (y1 > 0){
        if (isCollidingBottom(x1, y1, Realx, Realy)){
            OnGround = true;
            y1 = 0;
        }else{
            OnGround = false;
        }
    }


    if (isColliding(x1, y1, Realx, Realy)){
        return;
    }
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
    }
    if (hasJump){ 
        verticalVelocity = -10; 
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