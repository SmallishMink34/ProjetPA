#include "player.hpp"
#include "../../Constante.cpp"

Player::Player(SDL_Renderer* Renderer){
    // Images, nom, vie, etc..
    
    this->vie = 3;
    this->x = 60;
    this->y = 60;
    this->speed = 5;
    
    this->Image = Sprite("src/Images/Player/Player_default.png", this->x, this->y, 32, 64);
    this->Image.loadImage(Renderer);
}

Player::~Player(){
    
}

void Player::Moveto(int x, int y){
    if (this->y+64+Gravity<=Windows_H){
        this->y = y;
    }else{
        this->y = Windows_H-64;
    }
    this->x = x;
    this->Image.Moveto(this->x, this->y);
}

void Player::Move(int x, int y){
    this->Moveto(this->x + x, this->y + y);
}

int Player::getX(){
    return this->x;
}

int Player::getY(){
    return this->y;
}

std::string Player::GetName(){
    return this->Nom;
}

void Player::SetName(const std::string Name){
    this->Nom = Name;
}