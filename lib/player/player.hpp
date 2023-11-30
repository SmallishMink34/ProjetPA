#ifndef DefPlayer
#define DefPlayer
#include <unistd.h>

#include <iostream>
#include <string>
#include <utility>  // Pour std::pair
#include <vector>

#include "../Cartes/cartes.hpp"
#include "../Variables/variables.hpp"
#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"
#include "../world/world.hpp"

class world;

class allMaps;
class Player {
 public:
  // Constructeur
  Player(SDL_Renderer* Renderer, Variable* Var);

  // Variables
  int vie;
  Sprite Image;
  Sprite hp;
  int speed;
  Variable* Var;

  // std::string etats[4] = {"Right", "Left", "Jump", "Idle"};
  std::map<std::string, std::vector<std::pair<int, int>>> etats;
  std::string etat;
  std::vector<tmx::Object> Collisions;

  // Fonctions
  std::string GetName();
  void SetName(const std::string Name);
  void Moveto();
  void RealMoveto(int x, int y);
  void Move(int x, int y);
  void AnimPlayer(int i);
  int getWidth();
  int getHeight();

  bool isColliding(int x1, int y1, int realx, int realy);
  std::vector<std::pair<tmx::Object, std::string>> isColliding(int realx, int realy);
  int getRX();
  int getRY();
  int getX();
  int getY();

  std::string toString();
  void InitPlayer(std::vector<tmx::Object> Objects, world* Monde);
  void FixCamera();
  void AllMove(int x1, int y1, bool Teleport);
  bool isOnGround();
  float getVerticalVelocity();
  void jump();
  bool isJumping();
  void setIsJumping(bool Jump);
  void applyGravity(float deltaTime);
  ~Player();
  float dy;

 private:
  std::string Nom;
  int x;
  int y;

  int Realx;
  int Realy;

  int oldRealx;
  int oldRealy;
  bool OnGround;
  bool Jumping;
  bool hasJump;
  float verticalVelocity;
  float jumpStrength;
  float jumpTime;
  allMaps* Map;
  world* Mondee;
};

#endif