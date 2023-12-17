#include "player.hpp"

#include <chrono>
#include <iostream>
#include <thread>

Player::Player(SDL_Renderer *Renderer) {
  vie = 10;
  x = 60;  // Coordonnées sur l'interface
  y = 60;
  Realx = 60;  // Coordonnées réels
  Realy = 60;
  speed = playerSpeed;
  width = 36;
  height = 96;
  dy = 0;
  verticalVelocity = 0.0f;
  jumpStrength = 8.0f;
  Jumping = true;
  OnGround = false;
  etat = "Right";
  Animcpt = 0;
  score = 0;

  mapDX = 0;
  mapDY = 0;

  Rwidth = 70;
  Rheight = 70;

  etats["Right"] = {{0, 910}, {82, 910}, {164, 910}, {246, 910}, {328, 910}, {410, 910}, {492, 910}, {574, 910}, {656, 910}};
  etats["Left"] = {{0, 744}, {82, 744}, {164, 744}, {246, 744}, {328, 744}, {410, 744}, {492, 744}, {574, 744}, {656, 744}};
  etats["Jump"] = {{0, 175}, {82, 175}, {164, 175}, {246, 175}, {328, 175}, {410, 175}};
  etats["Fall"] = {{328, 175}, {246, 175}, {164, 175}, {82, 175}, {0, 175}};
  etats["Idle"] = {{0, 910}};

  this->Renderer = Renderer;

  Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", x, y, 96, 96);
  Image.setSrcRect(0, 180, 64, 64);
  Image.loadImage(Renderer);
  this->Arme = std::unique_ptr<armes>(new armes(Renderer));

  this->jumpSound = Mix_LoadWAV("src/music/sounds/jump.MP3");
  this->boostJumpSound = Mix_LoadWAV("src/music/sounds/boost.MP3");
}

Player::~Player() {
  Mix_FreeChunk(jumpSound);
  Mix_FreeChunk(boostJumpSound);
}

void Player::InitPlayer(std::vector<tmx::Object> Collisions, std::vector<monster *> *Monsters) {
  this->Collisions = Collisions;
  this->Arme->setCollisions(Collisions, Monsters);
}

std::string Player::GetName() { return Nom; }

void Player::SetName(const std::string Name) { Nom = Name; }

std::string Player::toString() { return ("X : " + std::to_string(getX()) + " Y : " + std::to_string(getY())); }

int Player::getScore() { return score; }

void Player::IncrementScore(int value) { this->score += value; }

void Player::selfMove(bool Keys[4], int mouseX, int mouseY, int dx, int dy) {
  int moveX = 0;
  int moveY = 0;

  applyGravity();

  // Gérer les mouvements verticaux (haut / bas)
  if(Keys[2] && isOnGround()) {
    jump();
    Mix_PlayChannel(-1, jumpSound, 0);
  }

  // Gérer les déplacements horizontaux
  if(Keys[0]) {
    moveX = -speed;
  }

  if(Keys[1]) {
    moveX = speed;
  }

  if(Keys[3]) {
    if(isOnGround()) {
      moveY = speed;
    }
  }

  if(Keys[4]) {
    Arme->tir(getCX(), getCY(), getCRX(), getCRY(), mouseX, mouseY);
  }

  Move(moveX, moveY, dx, dy);

  if(moveX < 0) {
    etat = "Left";
  } else if(moveX > 0) {
    etat = "Right";
  } else if(moveX == 0 && moveY <= 1 && moveY >= -1) {
    etat = "Idle";
  }

  if(verticalVelocity < 0) {
    etat = "Jump";
  } else if(verticalVelocity > 0) {
    etat = "Fall";
  }
}

void Player::Move(int x1, int y1, int dxMap, int dyMap) {  // Pas les coordonnées, seulement le vecteur de déplacements
  std::vector<std::pair<tmx::Object, std::string>> result = isColliding(Realx, Realy);

  mapDX = dxMap;
  mapDY = dyMap;

  std::pair<tmx::Object, std::string> Down = isInList(result, "Down");
  std::pair<tmx::Object, std::string> Up = isInList(result, "Up");
  std::pair<tmx::Object, std::string> Left = isInList(result, "Left");
  std::pair<tmx::Object, std::string> Right = isInList(result, "Right");

  if(dy <= 0) {
    if(isEmpty(Down)) {
      OnGround = false;
      jumpStrength = JumpStrength;
    }
  }
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
      Mix_PlayChannel(-1, boostJumpSound, 0);
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