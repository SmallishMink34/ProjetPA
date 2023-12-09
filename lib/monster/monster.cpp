#include "monster.hpp"

monster::monster(SDL_Renderer* Renderer, Variable* Var) {
  this->Var = Var;
  speed = 5;
  width = 96;
  height = 96;
  vie = 3;
  dy = 0;
  verticalVelocity = 0.0f;
  Image = Sprite("src/Images/Monster/New Piskel.png", x, y, 96, 96);
  Image.loadImage(Renderer);
}

void monster::InitMonster(std::vector<tmx::Object> Collisions) { this->Collisions = Collisions; }
