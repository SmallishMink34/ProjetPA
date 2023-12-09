#include "player.hpp"

#include <chrono>
#include <iostream>
#include <thread>

Player::Player(SDL_Renderer *Renderer, Variable *Var) {
  vie = 3;
  x = 60;  // Coordonnées sur l'interface
  y = 60;
  Realx = 60;  // Coordonnées réels
  Realy = 60;
  this->Var = Var;
  speed = 5;
  width = 36;
  height = 96;
  dy = 0;
  verticalVelocity = 0.0f;
  jumpStrength = 8.0f;
  Jumping = true;
  hasJump = false;
  OnGround = false;
  etat = "Right";

  mapDX = 0;
  mapDY = 0;

  etats["Right"] = {{0, 910}, {82, 910}, {164, 910}, {246, 910}, {328, 910}, {410, 910}, {492, 910}, {574, 910}, {656, 910}};
  etats["Left"] = {{0, 744}, {82, 744}, {164, 744}, {246, 744}, {328, 744}, {410, 744}, {492, 744}, {574, 744}, {656, 744}};
  etats["Jump"] = {{246, 175}, {328, 175}, {410, 175}, {492, 175}, {82, 175}, {0, 175}, {0, 175}};
  etats["Idle"] = {{0, 910}};

  this->Renderer = Renderer;

  Image = Sprite("src/Images/Player/Player_default_Tilesheet.png", x, y, 96, 96);
  Image.setSrcRect(0, 180, 64, 64);
  Image.loadImage(Renderer);
  this->Arme = new armes(Renderer);
}

void Player::InitPlayer(std::vector<tmx::Object> Collisions, std::vector<monster *> *Monsters) {
  this->Collisions = Collisions;
  this->Arme->setCollisions(Collisions, Monsters);
}

void Player::AnimPlayer(int i) { Image.setSrcRect(etats[etat][i].first, etats[etat][i].second, 70, 70); }

std::string Player::GetName() { return Nom; }

void Player::SetName(const std::string Name) { Nom = Name; }

std::string Player::toString() { return ("X : " + std::to_string(getX()) + " Y : " + std::to_string(getY())); }
