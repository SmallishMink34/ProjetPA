#include "player.hpp"

#include <iostream>

#include "../../Constante.hpp"

Player::Player(SDL_Renderer *Renderer) {
  vie = 3;

  x = 60;  // Coordonnées sur l'interface
  y = 60;
  Realx = 60;  // Coordonnées réels
  Realy = 60;

  speed = 5;
  dy = 0;
  verticalVelocity = 0.0f;
  jumpStrength = JumpStrength;
  Jumping = true;
  hasJump = false;
  OnGround = false;

  Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", x, y, 54, 96);
  Image.setSrcRect(24, 180, 36, 64);
  Image.loadImage(Renderer);
}

void Player::InitPlayer(std::vector<tmx::Object> Objects, world *Monde) {
  Collisions = Objects;
  Map = Monde->Map;
  Mondee = Monde;
}

tmx::Object *Player::isColliding(int x1, int y1, int realx, int realy) {
  for(auto &collisionObject : Collisions) {
    if(realx + getWidth() + x1 > collisionObject.getPosition().x && realx + x1 < collisionObject.getPosition().x + collisionObject.getAABB().width &&
       realy + y1 + getHeight() > collisionObject.getPosition().y && realy + y1 < collisionObject.getPosition().y + collisionObject.getAABB().height) {
      if(collisionObject.getType() == "Platform") {
      } else if(collisionObject.getType() == "Collision") {
        return &collisionObject;
      }
    }
  }
  return nullptr;
}

bool isInBox(int x, int y, tmx::Object object) {
  if(x > object.getPosition().x && x < object.getPosition().x + object.getAABB().width && y > object.getPosition().y && y < object.getPosition().y + object.getAABB().height) {
    return true;
  }
  return false;
}

std::vector<std::pair<tmx::Object, std::string>> Player::isColliding(int realx, int realy) {
  std::vector<std::pair<tmx::Object, std::string>> CollidePairs;
  for(auto &collisionObject : Collisions) {
    if(isInBox(realx + speed, realy + getHeight() + 2, collisionObject) || (isInBox(realx + getWidth() - speed, realy + getHeight() + 2, collisionObject))) {
      CollidePairs.push_back(std::make_pair(collisionObject, "Down"));
    }
    if(isInBox(realx + getWidth() + speed, realy + getHeight() / 4, collisionObject) || (isInBox(realx + getWidth() + speed, realy + 3 * getHeight() / 4, collisionObject))) {
      if(collisionObject.getName() == "") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Right"));
      }
    }
    if(isInBox(realx - speed, realy + getHeight() / 4, collisionObject) || (isInBox(realx - speed, realy + 3 * getHeight() / 4, collisionObject))) {
      if(collisionObject.getName() == "") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Left"));
      }
    }
    if(isInBox(realx + speed, realy, collisionObject) || (isInBox(realx - speed + getWidth(), realy, collisionObject))) {
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

  Image.Moveto(x, y);
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

  std::cout << "Dy : " << dy << std::endl;

  if(dy <= 0) {
    if(isEmpty(isInList(result, "Down"))) {
      OnGround = false;
      jumpStrength = JumpStrength;
    }
  }

  if(!isEmpty(isInList(result, "Left"))) {
    AllMove(isInList(result, "Left").first.getPosition().x + isInList(result, "Left").first.getAABB().width + 2, Realy, true);
    if(x1 < 0) {
      x1 = 0;
    }
  } else if(!isEmpty(isInList(result, "Right"))) {
    AllMove(isInList(result, "Right").first.getPosition().x - getWidth() - 2, Realy, true);
    if(x1 > 0) {
      x1 = 0;
    }
  }
  if(!isEmpty(isInList(result, "Down")) && dy >= 0) {
    AllMove(Realx, isInList(result, "Down").first.getPosition().y - getHeight(), true);

    if(isInList(result, "Down").first.getName() == "Jump") {
      jumpStrength = (float)isInList(result, "Down").first.getProperties().front().getIntValue();
      jump();
    }

    if(y1 > 0 && isInList(result, "Down").first.getName() == "Platform") {
      AllMove(Realx, Realy + isInList(result, "Down").first.getAABB().height, true);
    }

    OnGround = true;
  } else if(!isEmpty(isInList(result, "Up"))) {
    AllMove(Realx, isInList(result, "Up").first.getPosition().y + isInList(result, "Up").first.getAABB().height + 2, true);
    verticalVelocity = 0;
  }
  AllMove(x1, y1, false);
}

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
  if(x > Map->getMapWidth() - Real_W / 2) {
    int nombre = Map->getMapWidth() - Real_W;
    x = x - nombre;
  }
  if(y > Map->getMapHeight() - Real_H / 2) {
    int nombre = Map->getMapHeight() - Real_H;
    y = y - nombre;
  }
  Image.Moveto(x, y);
}

void Player::applyGravity(float deltaTime) {
  dy = 0;
  verticalVelocity += Gravity;
  dy += verticalVelocity;

  if(isOnGround()) {
    dy = 0;
    verticalVelocity = 0;
    setIsJumping(false);
    if(hasJump) {  // Seulement si il est sur le sol
      verticalVelocity = -jumpStrength;
      dy += verticalVelocity;
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

int Player::getWidth() { return Image.getWidth(); }

int Player::getHeight() { return Image.getHeight(); }

bool Player::isOnGround() { return OnGround; }

void Player::jump() {
  if(isOnGround()) {
    hasJump = true;
  }
}

float Player::getVerticalVelocity() { return verticalVelocity; }

bool Player::isJumping() { return Jumping; }

void Player::setIsJumping(bool Jump) { Jumping = Jump; }