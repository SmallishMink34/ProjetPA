#include "player.hpp"

#include <iostream>

Player::Player(SDL_Renderer *Renderer, Variable *Var) {
  vie = 3;

  x = 60;  // Coordonnées sur l'interface
  y = 60;
  Realx = 60;  // Coordonnées réels
  Realy = 60;
  this->Var = Var;

  width = 36;
  height = 96;
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
  etats["Jump"] = {{246, 175}, {328, 175}, {410, 175}, {492, 175}, {410, 175}, {328, 175}};
  etats["Idle"] = {{0, 173}};

  Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", x, y, 96, 96);
  Image.setSrcRect(0, 180, 64, 64);
  Image.loadImage(Renderer);
}

bool isBoxInBox(tmx::Object object1, tmx::Object object2) {
  if(object1.getPosition().x < object2.getPosition().x + object2.getAABB().width && object1.getPosition().x + object1.getAABB().width > object2.getPosition().x &&
     object1.getPosition().y < object2.getPosition().y + object2.getAABB().height && object1.getPosition().y + object1.getAABB().height > object2.getPosition().y) {
    return true;
  }
  return false;
}

bool isBoxInBox(int x, int y, tmx::Object object) {
  if(x < object.getPosition().x + object.getAABB().width && x > object.getPosition().x && y < object.getPosition().y + object.getAABB().height && y > object.getPosition().y) {
    return true;
  }
  return false;
}

void Player::InitPlayer(std::vector<tmx::Object> Objects, world *Monde) {
  Collisions = Objects;
  Map = Monde->Map;
  Mondee = Monde;
}

bool Player::isColliding(int x1, int y1, int w, int h) {
  if(getRX() > x1 && getRX() < x1 + w && getRY() > y1 && getRY() < y1 + h) {
    return true;
  }
  return false;
}

bool isPointInBox(int x, int y, tmx::Object object) {
  if(x > object.getPosition().x && x < object.getPosition().x + object.getAABB().width && y > object.getPosition().y && y < object.getPosition().y + object.getAABB().height) {
    return true;
  }
  return false;
}

std::vector<std::pair<tmx::Object, std::string>> Player::isColliding(int realx, int realy) {
  std::vector<std::pair<tmx::Object, std::string>> CollidePairs;
  for(auto &collisionObject : Collisions) {
    if(isPointInBox(realx + speed, realy + getHeight() + 2, collisionObject) || (isPointInBox(realx + getWidth() - speed, realy + getHeight() + 2, collisionObject))) {
      CollidePairs.push_back(std::make_pair(collisionObject, "Down"));
    }
    if(isPointInBox(realx + getWidth() + speed, realy + getHeight() / 4, collisionObject) ||
       (isPointInBox(realx + getWidth() + speed, realy + 3 * getHeight() / 4, collisionObject))) {
      if(collisionObject.getName() == "") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Right"));
      }
    }
    if(isPointInBox(realx - speed, realy + getHeight() / 4, collisionObject) || (isPointInBox(realx - speed, realy + 3 * getHeight() / 4, collisionObject))) {
      if(collisionObject.getName() == "") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Left"));
      }
    }
    if(isPointInBox(realx + speed, realy, collisionObject) || (isPointInBox(realx - speed + getWidth(), realy, collisionObject))) {
      if(collisionObject.getName() == "") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Up"));
      }
    }
  }
  return CollidePairs;
}

Player::~Player() {}

void Player::Moveto() {
  x = Realx - Mondee->dx;
  y = Realy - Mondee->dy;

  Image.Moveto(x - getWidth(), y);
}

void Player::RealMoveto(int x1, int y1) {
  Realx = x1;
  Realy = y1;
}

std::pair<tmx::Object, std::string> isInList(std::vector<std::pair<tmx::Object, std::string>> list, std::string value) {
  for(int i = 0; i < (int)list.size(); i++) {
    if(list[i].second == value) {
      return list[i];
    }
  }
  return std::make_pair(tmx::Object(), "");  // Return an empty pair
}

bool isEmpty(std::pair<tmx::Object, std::string> pair) {
  if(pair.second == "") {
    return true;
  }
  return false;
}

void Player::Move(int x1, int y1) {  // Pas les coordonnées, seulement le vecteur de déplacements
  std::vector<std::pair<tmx::Object, std::string>> result = isColliding(Realx, Realy);

  if(dy <= 0) {
    if(isEmpty(isInList(result, "Down"))) {
      OnGround = false;
      jumpStrength = Var->JumpStrength;
    }
  }

  std::pair<tmx::Object, std::string> Down = isInList(result, "Down");
  std::pair<tmx::Object, std::string> Up = isInList(result, "Up");
  std::pair<tmx::Object, std::string> Left = isInList(result, "Left");
  std::pair<tmx::Object, std::string> Right = isInList(result, "Right");

  if(!isEmpty(Left)) {
    AllMove(Left.first.getPosition().x + Left.first.getAABB().width + 2, Realy, true);
    if(x1 < 0) {
      x1 = 0;
    }
  } else if(!isEmpty(Right)) {
    AllMove(Right.first.getPosition().x - getWidth() - 2, Realy, true);
    if(x1 > 0) {
      x1 = 0;
    }
  }
  if(!isEmpty(Down) && dy >= 0) {
    AllMove(Realx, Down.first.getPosition().y - getHeight(), true);
    if(Down.first.getName() == "Jump") {
      jumpStrength = (float)Down.first.getProperties().front().getIntValue();
      jump();
    }

    if(y1 > 0 && Down.first.getName() == "Platform") {
      AllMove(Realx, Realy + Down.first.getAABB().height, true);
    }

    OnGround = true;
  } else if(!isEmpty(Up)) {
    AllMove(Realx, Up.first.getPosition().y + Up.first.getAABB().height + 2, true);
    verticalVelocity = 0;
  }

  AllMove(x1, y1, false);
}

void Player::AnimPlayer(int i) { Image.setSrcRect(etats[etat][i].first, etats[etat][i].second, 70, 70); }

void Player::AllMove(int x1, int y1, bool Teleport) {
  if(!Teleport) {
    RealMoveto(Realx + x1, Realy + y1);
    Moveto();
  } else {
    RealMoveto(x1, y1);
    Moveto();
  }
}

void Player::FixCamera() {
  if(x > Map->getMapWidth() - Var->Real_W / 2) {
    int nombre = Map->getMapWidth() - Var->Real_W;
    x = x - nombre;
  }
  if(y > Map->getMapHeight() - Var->Real_H / 2) {
    int nombre = Map->getMapHeight() - Var->Real_H;
    y = y - nombre;
  }
  Image.Moveto(x, y);
}

void Player::applyGravity(float deltaTime) {
  dy = 0;
  verticalVelocity += Var->Gravity;
  dy += verticalVelocity;
  if(verticalVelocity > maxSpeed) verticalVelocity = maxSpeed;

  // if(dy > 0.5 && !isOnGround()) {
  //   etat = "Idle";
  // }
  if(isOnGround()) {
    dy = 0;
    verticalVelocity = 0;
    setIsJumping(false);
    if(hasJump) {  // Seulement si il est sur le sol
      verticalVelocity = -jumpStrength;
      dy += verticalVelocity;
      etat = "Jump";
    }
  }

  if(!isJumping()) hasJump = false;

  Move(0, dy * deltaTime);
}

int Player::getRX() { return Realx; }

int Player::getRY() { return Realy; }

int Player::getX() { return x; }

int Player::getY() { return y; }

std::string Player::GetName() { return Nom; }

void Player::SetName(const std::string Name) { Nom = Name; }

std::string Player::toString() { return ("X : " + std::to_string(getX()) + " Y : " + std::to_string(getY())); }

int Player::getWidth() { return width; }

int Player::getHeight() { return height; }

bool Player::isOnGround() { return OnGround; }

void Player::jump() {
  if(isOnGround()) {
    hasJump = true;
  }
}

float Player::getVerticalVelocity() { return verticalVelocity; }

bool Player::isJumping() { return Jumping; }

void Player::setIsJumping(bool Jump) { Jumping = Jump; }

void Player::setVerticalVelocity(float velocity) { verticalVelocity = velocity; }