#include "armes.hpp"

armes::armes(SDL_Renderer* renderer) {
  this->degats = 1;
  this->portee = 50;
  this->cadence = 2;
  this->renderer = renderer;
  this->bullet = std::vector<balles*>();
  this->counter = -1;
}

void armes::setCollisions(std::vector<tmx::Object> collisions, std::vector<monster*>* MonstreList) {
  this->collisions = collisions;
  this->MonstreList = MonstreList;
}

void armes::tir(int PlayerX, int PlayerY, int PlayerRX, int PlayerRY, int mouseX, int mouseY) {
  float dirrectionX = (mouseX - PlayerX);
  float dirrectionY = (mouseY - PlayerY);

  float distanceSquared = dirrectionX * dirrectionX + dirrectionY * dirrectionY;
  float distance = sqrt(distanceSquared);

  if(distance != 0) {
    dirrectionX = dirrectionX / distance;
    dirrectionY = dirrectionY / distance;
  }

  if(counter == -1) {
    balles* balle = new balles(renderer, PlayerRX, PlayerRY, dirrectionX, dirrectionY, this->degats, this->portee);
    bullet.push_back(balle);
    counter = 0;
  }
}

void armes::update() {
  if(counter != -1) counter++;
  if(counter == cadence) {
    counter = -1;
  }

  for(long unsigned int i = 0; i < bullet.size(); i++) {
    bullet.at(i)->move();
    if(bullet.at(i)->update(collisions, MonstreList)) {
      delete bullet.at(i);
      bullet.erase(bullet.begin() + i);
    }
  }
}

void armes::draw(SDL_Renderer* renderer, int dx, int dy) {
  for(long unsigned int i = 0; i < bullet.size(); i++) {
    bullet.at(i)->draw(renderer, dx, dy);
  }
}

armes::~armes() {
  for(long unsigned int i = 0; i < bullet.size(); i++) {
    delete bullet.at(i);
  }
  std::cout << "Armes deleted" << std::endl;
}

balles::balles(SDL_Renderer* renderer, int x, int y, float dirrectionX, float dirrectionY, int degats, int portee) {
  this->vitesse = 12.0f;
  this->rect = {x, y, 10, 10};
  sprite = new Sprite("src/Images/Player/bullet.png", x, y, 30, 30);
  sprite->loadImage(renderer);
  this->dirrX = dirrectionX;
  this->dirrY = dirrectionY;
  this->counter = 0;
  this->degats = degats;
  this->portee = portee;
}

bool balles::update(std::vector<tmx::Object> collisions, std::vector<monster*>* MonstreList) {
  this->counter++;
  if(counter == this->portee) {
    return true;
  }

  for(auto& collisionObject : collisions) {
    if(isColliding(collisionObject) && collisionObject.getName() != "Platform" && collisionObject.getName() != "Jump") {
      return true;
    }
  }

  for(auto& monstre : *MonstreList) {
    if(isColliding(monstre)) {
      monstre->takeDamage(this->degats);
      if(monstre->getVie() <= 0) {
        MonstreList->erase(std::remove(MonstreList->begin(), MonstreList->end(), monstre), MonstreList->end());
      }
      return true;
    }
  }
  return false;
}

void balles::draw(SDL_Renderer* renderer, int dx, int dy) { sprite->selfDraw(renderer, this->rect.x - dx, this->rect.y - dy); }

void balles::move() {
  float resultX = dirrX * vitesse;
  float resultY = dirrY * vitesse;

  this->rect.x += resultX;
  this->rect.y += resultY;
}

bool balles::isColliding(tmx::Object object) {
  if(this->rect.x<object.getPosition().x + object.getAABB().width&& this->rect.x + this->rect.w> object.getPosition().x &&
     this->rect.y<object.getPosition().y + object.getAABB().height&& this->rect.y + this->rect.h> object.getPosition().y) {
    return true;
  }
  return false;
}

bool balles::isColliding(monster* monstre) {
  if(this->rect.x < monstre->getRX() + monstre->getWidth() && this->rect.x + this->rect.w > monstre->getRX() && this->rect.y < monstre->getRY() + monstre->getHeight() &&
     this->rect.y + this->rect.h > monstre->getRY()) {
    std::cout << "Y" << this->rect.y << " " << monstre->getRY() << " " << monstre->getHeight() << std::endl;
    return true;
  }
  return false;
}

balles::~balles() {
  if(sprite != nullptr) {
    delete sprite;
  }
}