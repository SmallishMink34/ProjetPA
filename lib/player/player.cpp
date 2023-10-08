#include "player.hpp"
#include "../../Constante.hpp"
#include <iostream>

Player::Player(SDL_Renderer* Renderer, level* Map){
    // Images, nom, vie, etc..
    
    this->vie = 3;
    this->x = 60;
    this->y = 60;
    this->Realx = 60;
    this->Realy = 60;
    this->speed = 5;
    this->Map = Map;
    
    this->Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", this->x, this->y, 36, 64);
    this->Image.setSrcRect(24, 180, 36, 64);
    this->Image.loadImage(Renderer);
}

void Player::InitPlayer(std::vector<tmx::Object> Objects){
    this->Collisions = Objects;
    std::cout << "Collisions : " << this->Collisions.size() << std::endl;
}

bool Player::isColliding(int x1, int y1){
    for (long unsigned int i = 0; i < this->Collisions.size(); i++){
        // Vérifier les collisions horizontales
        for (const auto& collisionObject : Collisions) {
            if (x1 + getWidth() > collisionObject.getPosition().x &&
                x1 < collisionObject.getPosition().x + collisionObject.getAABB().width &&
                y1 + getHeight() > collisionObject.getPosition().y &&
                y1 < collisionObject.getPosition().y + collisionObject.getAABB().height) {
                // Collision horizontale détectée
                return true;
            }
        }
    }
    return false;
}

Player::~Player(){
    
}

void Player::Moveto(int x, int y){

       
    if (!(this->Realx > Real_W/2-this->speed && this->Realx-this->speed < this->Map->getMapWidth() - Real_W/2)){
        this->x = x;
    }else{
        this->x = Real_W/2;
    }
    if (!(this->Realy > Real_H/2-this->speed && this->Realy-this->speed < this->Map->getMapHeight() - Real_H/2)){
        this->y = y;
    }else{
        this->y = Real_H/2;
    }
    this->Image.Moveto(this->x, this->y);
}

void Player::RealMoveto(int x, int y){
    this->Realx = x;
    this->Realy = y;
}

void Player::Move(int x1, int y1){
    if (isColliding(this->Realx +x1, this->Realy +y1)){ // Modifier afin de faire coller les collisions au sprite
        return;
    }
    this->Moveto(this->x + x1, this->y + y1);
    this->RealMoveto(this->Realx + x1, this->Realy + y1);
}

void Player::FixCamera(){
    if (this->x > this->Map->getMapWidth() - Real_W/2){
        int nombre = this->Map->getMapWidth()-Real_W;
        this->x = this->x - nombre;
        std::cout << "X : " << this->x << std::endl;
    }
    if (this->y > this->Map->getMapHeight() - Real_H/2){
        int nombre = this->Map->getMapHeight()-Real_H;
        this->y = this->y - nombre;
    }
    this->Image.Moveto(this->x, this->y);
}

int Player::getX(){
    return this->Realx;
}

int Player::getY(){
    return this->Realy;
}

std::string Player::GetName(){
    return this->Nom;
}

void Player::SetName(const std::string Name){
    this->Nom = Name;
}

std::string Player::toString(){
    return ("X : " + std::to_string(this->x) + " Y : " + std::to_string(this->y));
}

int Player::getWidth(){
    return this->Image.getWidth();
}

int Player::getHeight(){
    return this->Image.getHeight();
}