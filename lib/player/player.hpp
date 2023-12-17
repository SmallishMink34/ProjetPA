#ifndef DefPlayer
#define DefPlayer
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h>

#include <iostream>
#include <memory>
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
  Player(SDL_Renderer* Renderer);
  ~Player();

  // Variables
  std::unique_ptr<armes> Arme;

  // Fonctions

  // Getters
  std::string GetName();
  int getScore();

  // Setters
  void SetName(const std::string Name);
  void IncrementScore(int value);
  // Autres
  void InitPlayer(std::vector<tmx::Object> Collisions, std::vector<monster*>* Monsters);
  void selfMove(bool Keys[4], int mouseX, int mouseY, int dx, int dy);
  std::string toString();

  void Move(int moveX, int moveY, int dx, int dy) override;

 private:
  std::string Nom;
  Mix_Chunk* jumpSound;
  Mix_Chunk* boostJumpSound;

  int score;
  SDL_Renderer* Renderer;
  allMaps* Map;
};

#endif