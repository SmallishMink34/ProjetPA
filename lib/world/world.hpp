#ifndef DefWorld
#define DefWorld

#include "../Cartes/cartes.hpp"
#include "../HUD/hud.hpp"
#include "../Variables/variables.hpp"
#include "../display/display.hpp"
#include "../donjon/donjon.hpp"
#include "../maps/maps.hpp"
#include "../player/player.hpp"
#include "../weapon/armes.hpp"

class allMaps;
class world {
 public:
  // Constucteur

  world(SDL_Renderer* Renderer, Variable* Var);
  ~world();
  // Variables
  Player* Joueur;
  Texture AllElements;
  allMaps* Map;
  HUD* hud;
  bool KeyPressed[5] = {false, false, false, false, false};  // 0 = left, 1 = right, 2 = up, 3 = down, 4 = click

  int dx;  // Décalage X de la map par rapport au personnage.
  int dy;

  int mouseX;
  int mouseY;

  Variable* Var;
  donjon* Donjon;
  bool seeMap;

  Uint32 currentTime;
  double deltaTime;
  Uint32 previousTime;
  Uint32 Animcpt;
  Uint32 cptest;

  // Fonctions
  void InitMonde(SDL_Renderer* Renderer);
  void drawAll(SDL_Renderer* Renderer);
  void movePlayer();
  void UpdateAll();
  void moveCamera();
  void FixCamera();
  void drawMap(SDL_Renderer* Renderer);
};

#endif