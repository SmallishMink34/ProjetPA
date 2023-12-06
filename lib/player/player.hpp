#ifndef DefPlayer
#define DefPlayer
#include <unistd.h>

#include <iostream>
#include <string>
#include <utility>  // Pour std::pair
#include <vector>

#include "../Variables/variables.hpp"
#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"
#include "../weapon/armes.hpp"

class allMaps;
class Player {
 public:
  // Constructeur
  Player(SDL_Renderer* Renderer, Variable* Var);

  // Variables

  Sprite Image;
  Sprite hp;
  int speed;
  Variable* Var;
  armes* Arme;

  // std::string etats[4] = {"Right", "Left", "Jump", "Idle"};
  std::map<std::string, std::vector<std::pair<int, int>>> etats;
  std::string etat;
  std::vector<tmx::Object> Collisions;

  // Fonctions

  // Getters
  std::string GetName();
  int getRX();
  int getRY();
  int getX();
  int getY();
  int getWidth();
  int getHeight();
  float getVerticalVelocity();
  bool isJumping();
  bool isOnGround();
  int getVie();

  // Setters
  void SetName(const std::string Name);
  void setIsJumping(bool Jump);
  void setVerticalVelocity(float velocity);
  void setX(int x);
  void setY(int y);
  void IncrementVie(int vie);

  // Collisions
  bool isColliding(int x1, int y1, int realx, int realy);
  std::vector<std::pair<tmx::Object, std::string>> isColliding(int realx, int realy);
  tmx::Object isColliding(std::vector<tmx::Object> Collisions);

  // Deplacements
  void Moveto();
  void RealMoveto(int x, int y);
  void Move(int x, int y, int dx, int dy);
  void AllMove(int x1, int y1, bool Teleport);
  void jump();

  // Autres
  void InitPlayer(std::vector<tmx::Object> Collisions);
  void AnimPlayer(int i);
  std::string toString();
  void applyGravity(float deltaTime);
  float dy;

  ~Player();

 private:
  std::string Nom;
  int x;
  int y;
  int Realx;
  int Realy;
  int vie;

  int width;
  int height;

  bool OnGround;
  bool Jumping;
  bool hasJump;
  float verticalVelocity;
  float jumpStrength;
  float jumpTime;

  SDL_Renderer* Renderer;

  int mapDX;
  int mapDY;
  allMaps* Map;
};

#endif