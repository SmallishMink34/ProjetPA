#ifndef DefPlayer
#define DefPlayer
#include <unistd.h>

#include <iostream>
#include <string>
#include <utility>  // Pour std::pair
#include <vector>

#include "../Variables/variables.hpp"
#include "../entity/entity.hpp"
#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"
#include "../weapon/armes.hpp"

class allMaps;
class Player: public Entity {
 public:
  // Constructeur
  Player(SDL_Renderer* Renderer, Variable* Var);

  // Variables
  armes* Arme;

  // std::string etats[4] = {"Right", "Left", "Jump", "Idle"};
  std::map<std::string, std::vector<std::pair<int, int>>> etats;
  std::string etat;

  // Fonctions

  // Getters
  std::string GetName();

  // Setters
  void SetName(const std::string Name);

  // Autres
  void InitPlayer(std::vector<tmx::Object> Collisions, std::vector<monster*>* Monsters);
  void AnimPlayer(int i);
  std::string toString();

 private:
  std::string Nom;

  SDL_Renderer* Renderer;

  int mapDX;
  int mapDY;
  allMaps* Map;
};

#endif