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
  aiDirrection = "Right";

  etat = "Right";
  etats["Right"] = {{0, 910}, {82, 910}, {164, 910}, {246, 910}, {328, 910}, {410, 910}, {492, 910}, {574, 910}, {656, 910}};
  etats["Left"] = {{0, 744}, {82, 744}, {164, 744}, {246, 744}, {328, 744}, {410, 744}, {492, 744}, {574, 744}, {656, 744}};
  etats["Jump"] = {{246, 175}, {328, 175}, {410, 175}, {492, 175}, {82, 175}, {0, 175}, {0, 175}};
  etats["Idle"] = {{0, 910}};
}

void monster::InitMonster(std::vector<tmx::Object> Collisions) { this->Collisions = Collisions; }

void monster::ai(int dx, int dy) {
  if(aiDirrection == "Right") {
    Move(speed, 0, dx, dy);
  } else if(aiDirrection == "Left") {
    // Move(-speed, 0, dx, dy);
  }

  if(std::rand() % 100 == 0) {
    // jump();
  }
}

void monster::Move(int x1, int y1, int dxMap, int dyMap) {  // Pas les coordonnées, seulement le vecteur de déplacements
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
      jumpStrength = Var->JumpStrength;
    }
  }
  if(!isEmpty(Left)) {
    aiDirrection = "Right";
    AllMove(Left.first.getPosition().x + Left.first.getAABB().width + 2, Realy, true);
    if(x1 < 0) {
      x1 = 0;
    }
  } else if(!isEmpty(Right)) {
    aiDirrection = "Left";
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