#ifndef ARMES_HPP
#define ARMES_HPP
#include <iostream>
#include <memory>
#include <vector>

#include "../maps/maps.hpp"
#include "../monster/monster.hpp"
#include "../sprites/sprite.hpp"

class balles {
 public:
  balles(SDL_Renderer* renderer, int x, int y, float dirrectionX, float dirrectionY, int degats, int portee);
  ~balles();
  void move();
  bool update(std::vector<tmx::Object> collisions, std::vector<monster*>* MonstreList);
  void draw(SDL_Renderer* renderer, int dx, int dy);
  bool isColliding(tmx::Object object);
  bool isColliding(monster* monstre);

 private:
  float vitesse;
  float dirrX;
  float dirrY;
  int degats;
  int portee;
  int counter;
  Sprite* sprite;
  SDL_Rect rect;
};

class armes {
 public:
  armes(SDL_Renderer* renderer);
  ~armes();
  void setCollisions(std::vector<tmx::Object> collisions, std::vector<monster*>* MonstreList);
  void tir(int PlayerX, int PlayerY, int PlayerRX, int PlayerRY, int mouseX, int mouseY);
  void draw(SDL_Renderer* renderer, int dx, int dy);
  void update();

 private:
  int degats;
  int portee;
  int cadence;
  int counter;
  std::vector<tmx::Object> collisions;
  std::vector<monster*>* MonstreList;
  SDL_Renderer* renderer;
  std::vector<balles*> bullet;
};

#endif