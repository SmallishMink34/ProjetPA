#include "monster.hpp"

monster::monster(SDL_Renderer* Renderer, Variable* Var) {
  this->Var = Var;
  speed = 5;
  width = 96;
  height = 96;
  vie = 3;
  dy = 0;
  verticalVelocity = 0.0f;
  Image = Sprite("src/Images/Monster/Monster1.png", x, y, 96, 96);
  Image.setSrcRect(0, 0, 64, 64);
  Image.loadImage(Renderer);

  etat = "Right";
  etats["Right"] = {{0, 910}, {82, 910}, {164, 910}, {246, 910}, {328, 910}, {410, 910}, {492, 910}, {574, 910}, {656, 910}};
  etats["Left"] = {{0, 744}, {82, 744}, {164, 744}, {246, 744}, {328, 744}, {410, 744}, {492, 744}, {574, 744}, {656, 744}};
  etats["Jump"] = {{246, 175}, {328, 175}, {410, 175}, {492, 175}, {82, 175}, {0, 175}, {0, 175}};
  etats["Idle"] = {{0, 910}};
}

void monster::InitMonster(std::vector<tmx::Object> Collisions) { this->Collisions = Collisions; }
