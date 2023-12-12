
#include "entity.hpp"

Entity::Entity() {
  vie = 0;
  speed = 0;
  x = 0;
  y = 0;
  Realx = 0;
  Realy = 0;
  width = 0;
  height = 0;
  dy = 0;
  deltax = 0;
  deltay = 0;
  mapDX = 0;
  mapDY = 0;
  verticalVelocity = 0;
  jumpStrength = 0;
  OnGround = false;
  Jumping = false;
  hasJump = false;
  canTakeDamage = false;
  istakeDamage = false;
  previousDamageTime = 0;
  etat = "Idle";
}

Entity::~Entity() {}

// Getters
int Entity::getVie() { return vie; }

int Entity::getX() { return x; }

int Entity::getY() { return y; }

int Entity::getRX() { return Realx; }

int Entity::getRY() { return Realy; }

int Entity::getWidth() { return width; }

int Entity::getHeight() { return height; }

// Setters

void Entity::setX(int x) { this->x = x; }

void Entity::setY(int y) { this->y = y; }

// Collisions

bool Entity::isColliding(int x, int y, int w, int h) {
  int rect1Left = x;
  int rect1Right = x + w;
  int rect1Top = y;
  int rect1Bottom = y + h;

  int rect2Left = getRX();
  int rect2Right = getRX() + getWidth();
  int rect2Top = getRY();
  int rect2Bottom = getRY() + getHeight();
  if(rect1Left <= rect2Right && rect1Right >= rect2Left && rect1Top <= rect2Bottom && rect1Bottom >= rect2Top) {
    return true;
  }
  return false;
}

std::vector<std::pair<tmx::Object, std::string>> Entity::isColliding(int realx, int realy) {
  std::vector<std::pair<tmx::Object, std::string>> CollidePairs;

  for(auto& collisionObject : Collisions) {
    if(isPointInBox(realx + speed, realy + getHeight() + speed, collisionObject) || (isPointInBox(realx + getWidth() - speed, realy + getHeight() + speed, collisionObject))) {
      CollidePairs.push_back(std::make_pair(collisionObject, "Down"));
    }
    if(isPointInBox(realx + getWidth() + speed, realy + getHeight() / 4, collisionObject) ||
       (isPointInBox(realx + getWidth() + speed, realy + 3 * getHeight() / 4, collisionObject)) ||
       isPointInBox(realx + getWidth() + speed, realy + getHeight() / 2, collisionObject)) {
      if(collisionObject.getName() != "Platform" && collisionObject.getName() != "Jump") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Right"));
      }
    }
    if(isPointInBox(realx - speed, realy + getHeight() / 4, collisionObject) || (isPointInBox(realx - speed, realy + 3 * getHeight() / 4, collisionObject))) {
      if(collisionObject.getName() != "Platform" && collisionObject.getName() != "Jump") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Left"));
      }
    }
    if(isPointInBox(realx + speed, realy, collisionObject) || (isPointInBox(realx - speed + getWidth(), realy, collisionObject))) {
      if(collisionObject.getName() != "Platform" && collisionObject.getName() != "Jump") {
        CollidePairs.push_back(std::make_pair(collisionObject, "Up"));
      }
    }
  }
  return CollidePairs;
}

tmx::Object Entity::isColliding(std::vector<tmx::Object> Collisions) {
  tmx::Object Collision;
  for(long unsigned int i = 0; i < Collisions.size(); i++) {
    if(isColliding(Collisions[i].getPosition().x, Collisions[i].getPosition().y, Collisions[i].getAABB().width, Collisions[i].getAABB().height)) {
      Collision = Collisions[i];
      break;
    }
  }

  return Collision;
}

void Entity::Moveto() {
  x = Realx - mapDX;
  y = Realy - mapDY;

  Image.Moveto(x - getWidth(), y);
}
void Entity::RealMoveto(int x1, int y1) {
  Realx = x1;
  Realy = y1;
}
void Entity::Move(int x1, int y1, int dxMap, int dyMap) {  // Pas les coordonnées, seulement le vecteur de déplacements
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
void Entity::AllMove(int x1, int y1, bool Teleport) {
  if(!Teleport) {
    RealMoveto(Realx + x1, Realy + y1);
    Moveto();
  } else {
    RealMoveto(x1, y1);
    Moveto();
  }
}

void Entity::jump() {
  if(isOnGround()) {
    hasJump = true;
  }
}

bool Entity::isOnGround() { return OnGround; }

float Entity::getVerticalVelocity() { return verticalVelocity; }

bool Entity::isJumping() { return Jumping; }

void Entity::applyGravity() {
  dy = 0;
  verticalVelocity += Gravity;
  dy += verticalVelocity;
  if(verticalVelocity > maxSpeed) verticalVelocity = maxSpeed;

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

  Move(0, dy, mapDX, mapDY);
}

void Entity::setIsJumping(bool Jump) { Jumping = Jump; }

void Entity::setVerticalVelocity(float velocity) { verticalVelocity = velocity; }

void Entity::IncrementVie(int vie) { this->vie += vie; }

bool Entity::takeDamage(int damage) {
  // TODO : Add sound
  if(canTakeDamage) {
    IncrementVie(-damage);
    std::cout << "Vie : " << vie << std::endl;
    canTakeDamage = false;
    istakeDamage = true;
  }

  if(vie <= 0) {
    return true;
  }
  return false;
}

void Entity::update(Uint32 currentTime) {
  if(istakeDamage) {
    istakeDamage = false;
    previousDamageTime = currentTime;
  }

  if(!canTakeDamage) {
    std::cout << (currentTime - previousDamageTime) / 1000.0f << std::endl;
    if((currentTime - previousDamageTime) / 1000.0f > InvincibilityTime) {
      canTakeDamage = true;
      previousDamageTime = currentTime;
    }
  }

  if(deltax != 0) {
    Move(deltax, 0, mapDX, mapDY);
    if(deltax > 0) {
      deltax -= 1;
    } else if(deltax < 0) {
      deltax += 1;
    }
  }

  if(deltay != 0) {
    Move(0, deltay, mapDX, mapDY);
    if(deltay > 0) {
      deltay -= 1;
    } else if(deltay < 0) {
      deltay += 1;
    }
  }

  if(vie <= 0) {
    vie = 0;
  }
}

void Entity::AnimEntity(int i) {
  if(etat != "Jump") {
    if(i % 5 == 0) {
      this->Animcpt++;
    }
  } else {
    if(i % 12 == 0) {
      this->Animcpt++;
    }
  }
  if(Animcpt > etats[etat].size() - 1) {
    Animcpt = 0;
  }
  Image.setSrcRect(etats[etat][Animcpt].first, etats[etat][Animcpt].second, 70, 70);
}

bool Entity::isCollidingEntity(Entity* entity) {
  if(isColliding(entity->getRX(), entity->getRY(), entity->getWidth(), entity->getHeight())) {
    return true;
  }
  return false;
}

int Entity::getCRX() { return getRX() + getWidth() / 2; }

int Entity::getCRY() { return getRY() + getHeight() / 2; }

int Entity::getCX() { return getX() + getWidth() / 2; }

int Entity::getCY() { return getY() + getHeight() / 2; }

void Entity::knockback(Entity* monstre) {
  float dx = getCRX() - monstre->getCRX();
  float dy = getCRY() - monstre->getCRY();
  float magnitude = sqrt(dx * dx + dy * dy);
  if(magnitude != 0) {
    dx /= magnitude;
    dy /= magnitude;
  }
  deltax = dx * RECUL;
  deltay = dy * RECUL;
}