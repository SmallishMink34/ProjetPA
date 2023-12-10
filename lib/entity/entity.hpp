#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include "../Variables/variables.hpp"
#include "../entity/entity.hpp"
#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"
#include "../utility/utility.hpp"

class Entity {
 public:
  // Constructeur par défaut
  Entity();

  // Destructeur virtuel
  virtual ~Entity();

  // Getters
  virtual int getVie();
  virtual int getX();
  virtual int getY();
  virtual int getRX();
  virtual int getRY();
  virtual int getWidth();
  virtual int getHeight();

  // Setters
  virtual void setX(int x);
  virtual void setY(int y);
  void setIsJumping(bool Jump);
  void setVerticalVelocity(float velocity);
  virtual void IncrementVie(int vie);

  // Deplacements
  virtual void Moveto();
  virtual void RealMoveto(int x, int y);
  virtual void Move(int x, int y, int dxMap, int dyMap);
  virtual void AllMove(int x1, int y1, bool Teleport);
  virtual void jump();

  virtual float getVerticalVelocity();
  virtual bool isJumping();
  virtual bool isOnGround();

  virtual void applyGravity();

  // Collisions
  virtual bool isColliding(int x, int y, int w, int h);
  virtual std::vector<std::pair<tmx::Object, std::string>> isColliding(int realx, int realy);
  virtual tmx::Object isColliding(std::vector<tmx::Object> Collisions);
  virtual bool isCollidingEntity(Entity* entity);
  std::vector<tmx::Object> Collisions;

  // Others
  virtual void update(Uint32 currentTime);
  virtual bool takeDamage(int damage);

  int vie;
  int speed;
  int x;
  int y;
  int width;
  int height;
  int Realx;
  int Realy;

  int mapDX;
  int mapDY;
  Variable* Var;
  Sprite Image;

  std::map<std::string, std::vector<std::pair<int, int>>> etats;
  std::string etat;

  void AnimEntity(int i);

  Uint32 previousDamageTime;

  bool OnGround;
  bool Jumping;
  bool hasJump;
  bool canTakeDamage;
  float verticalVelocity;
  float jumpStrength;
  float jumpTime;
  float dy;
};

#endif