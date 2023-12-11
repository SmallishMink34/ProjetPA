#ifndef Monster_HPP
#define Monster_HPP

#include <iostream>

#include "../entity/entity.hpp"

class monster: public Entity {
 public:
  // Constructeur
  monster(SDL_Renderer* Renderer, Variable* Var);

  // Variables

  // Fonctions
  void InitMonster(std::vector<tmx::Object> Collisions);
  void ai(int dx, int dy);
  void Move(int x1, int y1, int dxMap, int dyMap) override;

 private:
  // Variables
  std::string aiDirrection;
  std::string Nom;
};

#endif