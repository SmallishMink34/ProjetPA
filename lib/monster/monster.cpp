#include "monster.hpp"

monster::monster(SDL_Renderer* Renderer) {
  speed = 5;
  width = 64;
  height = 96;
  vie = 3;
  dy = 0;
  verticalVelocity = 0.0f;
  Image = Sprite("src/Images/Monster/Monster1.png", x, y, 96, 96);
  Rwidth = 64;
  Rheight = 64;
  Image.setSrcRect(0, 0, Rwidth, Rheight);
  Image.loadImage(Renderer);
  aiDirrection = "Right";

  int decalX = 10;

  etat = "Right";

  for(int i = 0; i < 9; i++) etats["Right"].push_back({decalX + i * 64, 704});

  for(int i = 0; i < 9; i++) etats["Left"].push_back({decalX + i * 64, 576});

  for(int i = 0; i < 7; i++) etats["Jump"].push_back({decalX + i * 64, 128});

  for(int i = 5; i >= 0; i--) etats["Fall"].push_back({decalX + i * 64, 128});
  etats["Idle"] = {{0, 910}};
}

void monster::InitMonster(std::vector<tmx::Object> Collisions) { this->Collisions = Collisions; }

void monster::ai(int dx, int dy) {
  int moveX = 0;
  int moveY = 0;

  if(aiDirrection == "Right") {
    moveX = speed;
  } else if(aiDirrection == "Left") {
    moveX = -speed;
  }

  if(std::rand() % 100 == 0) {
    jump();
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
      jumpStrength = JumpStrength;
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