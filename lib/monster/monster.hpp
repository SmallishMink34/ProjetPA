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

 private:
  std::string Nom;
};

#endif