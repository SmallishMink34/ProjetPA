#include "player.hpp"


Player::Player(SDL_Renderer* Renderer, Variable* Var){
    vie = 3;

    x = 60; // Coordonnées sur l'interface
    y = 60;
    Realx = 60; // Coordonnées réels
    Realy = 60;
    this->Var = Var;

    speed = 5;
    dy = 0;
    verticalVelocity = 0.0f;
    jumpStrength = 8.0f;
    Jumping = true;
    hasJump = false;
    OnGround = false;
    etat = "Idle";

    etats["Right"] = {{0, 910}, {82, 910}, {164, 910}, {246, 910}, {328, 910}, {410, 910}, {492, 910}, {574, 910}, {656, 910}};
    etats["Left"] = {{0, 744}, {82, 744}, {164, 744}, {246, 744}, {328, 744}, {410, 744}, {492, 744}, {574, 744}, {656, 744}};
    etats["Jump"] = {{0,9}};
    etats["Idle"] = {{0,173}};

    Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", x, y, 36, 64);
    Image.setSrcRect(0+24,9+7, 36, 64);
    Image.loadImage(Renderer);
}

void Player::InitPlayer(std::vector<tmx::Object> Objects, world* Monde){
    Collisions = Objects;
    std::cout << "Collisions : " << Collisions.size() << std::endl;
    Map = Monde->Map;
    Mondee = Monde;
}

tmx::Object* Player::isColliding(int x1, int y1, int realx, int realy){
    for (auto& collisionObject : Collisions) {
        if (realx + getWidth() + x1 > collisionObject.getPosition().x &&
            realx + x1 < collisionObject.getPosition().x + collisionObject.getAABB().width &&
            realy + y1 + getHeight() > collisionObject.getPosition().y &&
            realy + y1 < collisionObject.getPosition().y + collisionObject.getAABB().height) 
        {   
            return &collisionObject;
        }
    }
    return nullptr;
}

Player::~Player(){
    
}

void Player::Moveto(){
    x = Realx - Mondee->dx;
    y = Realy - Mondee->dy;

    Image.Moveto(x, y);
}

void Player::RealMoveto(int x1, int y1){
    Realx = x1;
    Realy = y1;
}

void Player::Move(int x1, int y1){ // Pas les coordonnées, seulement le vecteur de déplacements
    tmx::Object* object = isColliding(x1, y1, Realx, Realy);
    OnGround = false;
    if (object != nullptr){
        //printf("Collision\n");
        if (x1 > 0){
            AllMove(object->getPosition().x - getWidth(), Realy, true);
        }else if(x1 < 0){
            AllMove(object->getPosition().x + object->getAABB().width+5, Realy, true);
        }
        if (y1 > 0){
            AllMove(Realx, object->getPosition().y - getHeight(), true);
            OnGround = true;
        }else if(y1 < 0){
            AllMove(Realx, object->getPosition().y + object->getAABB().height, true);
            verticalVelocity = 0;
        }
    }else{
        AllMove(x1, y1, false);
    }
}

void Player::AnimPlayer(int i){
    Image.setSrcRect(etats[etat][i].first+24, etats[etat][i].second+7, 36, 64);
    //printf("coord : %d %d\n", etats[etat][i].first, etats[etat][i].second);
    //printf("etat : %s\n", etat.c_str());  
}

void Player::AllMove(int x1, int y1, bool Teleport){
    if (!Teleport){
        RealMoveto(Realx + x1, Realy + y1);
        Moveto();
    }else{
        RealMoveto(x1, y1);
        Moveto();
    }
}

void Player::FixCamera(int Real_W, int Real_H){
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
    verticalVelocity += Var->Gravity;
    dy += verticalVelocity;

    if (dy > 0.5 && !isOnGround()){
        etat = "Idle";
    }

    if (isOnGround()){ 
        dy = 0;
        verticalVelocity = 0;
        setIsJumping(false);
        if (hasJump){ // Seulement si il est sur le sol
            verticalVelocity = -jumpStrength;; 
            etat = "Jump";
        }
    }
    
    if (!isJumping()) hasJump = false;
    Move(0, dy * deltaTime); 
}

int Player::getRX(){
    return Realx;
}

int Player::getRY(){
    return Realy;
}

int Player::getX(){
    return x;
}

int Player::getY(){
    return y;
}

std::string Player::GetName(){
    return Nom;
}

void Player::SetName(const std::string Name){
    Nom = Name;
}

std::string Player::toString(){
    return ("X : " + std::to_string(getX()) + " Y : " + std::to_string(getY()));
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