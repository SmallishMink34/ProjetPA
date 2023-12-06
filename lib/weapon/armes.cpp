#include "armes.hpp"

armes::armes(SDL_Renderer* renderer) {
  this->degats = 0;
  this->portee = 50;
  this->cadence = 8;
  this->renderer = renderer;
  this->bullet = std::vector<balles>();
  this->counter = -1;
}

armes::~armes() {}

void armes::setCollisions(std::vector<tmx::Object> collisions) { this->collisions = collisions; }

void armes::tir(int PlayerX, int PlayerY, int PlayerRX, int PlayerRY, int mouseX, int mouseY) {
  float dirrectionX = (mouseX - PlayerX);
  float dirrectionY = (mouseY - PlayerY);

  float distance = sqrt(dirrectionX * dirrectionX + dirrectionY * dirrectionY);

  if(distance != 0) {
    dirrectionX = dirrectionX / distance;
    dirrectionY = dirrectionY / distance;
  }

  if(counter == -1) {
    std::cout << "Dirrection :" << dirrectionX << " " << dirrectionY << std::endl;
    balles balle = balles(renderer, PlayerRX, PlayerRY, dirrectionX, dirrectionY, this->degats, this->portee);
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
    bullet.at(i).move();
    if(bullet.at(i).update(collisions)) {
      bullet.erase(bullet.begin() + i);
    }
  }
}

void armes::draw(SDL_Renderer* renderer, int dx, int dy) {
  for(long unsigned int i = 0; i < bullet.size(); i++) {
    bullet.at(i).draw(renderer, dx, dy);
  }
}

balles::balles(SDL_Renderer* renderer, int x, int y, float dirrectionX, float dirrectionY, int degats, int portee) {
  this->vitesse = 7.0f;
  this->rect = {x, y, 10, 10};
  sprite = Sprite("src/Images/Player/bullet.png", x, y, 30, 30);
  sprite.loadImage(renderer);
  this->dirrX = dirrectionX;
  this->dirrY = dirrectionY;
  this->counter = 0;
  this->degats = degats;
  this->portee = portee;
}

bool balles::update(std::vector<tmx::Object> collisions) {
  this->counter++;
  if(counter == this->portee) {
    return true;
  }

  for(auto& collisionObject : collisions) {
    if(isColliding(collisionObject) && collisionObject.getName() != "Platform" && collisionObject.getName() != "Jump") {
      return true;
    }
  }
  return false;
}

void balles::draw(SDL_Renderer* renderer, int dx, int dy) { sprite.selfDraw(renderer, this->rect.x - dx, this->rect.y - dy); }

void balles::move() {
  this->rect.x += vitesse * dirrX;
  this->rect.y += vitesse * dirrY;
}

bool balles::isColliding(tmx::Object object) {
  if(this->rect.x<object.getAABB().left + object.getAABB().width&& this->rect.x + this->rect.w> object.getAABB().left &&
     this->rect.y<object.getAABB().top + object.getAABB().height&& this->rect.y + this->rect.h> object.getAABB().top) {
    return true;
  }
  return false;
}

balles::~balles() {}