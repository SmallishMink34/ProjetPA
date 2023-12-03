#ifndef DefCartes
#define DefCartes
#include <SDL2/SDL.h>

#include <iostream>
#include <map>
#include <string>

#include "../donjon/donjon.hpp"
#include "../maps/maps.hpp"
#include "../player/player.hpp"
#include "../world/world.hpp"
class Player;
class world;
class Cartes {
 private:
  SDL_Renderer* Renderer;
  std::string file;
  level* Map;
  std::vector<tmx::Object> Collisions;
  std::map<std::string, tmx::Object> Spawn;
  std::vector<tmx::Object> Elements;

 public:
  Cartes(SDL_Renderer* Renderer, std::string file);
  ~Cartes();
  level* getMap();
  void draw(SDL_Renderer* Renderer, int dx, int dy);
  std::vector<tmx::Object> getCollisions();
  std::vector<tmx::Object> getElements();
  tmx::Object getSpawn(std::string a);
};

class allMaps {
 private:
  donjon* Donjon;
  std::map<char, Cartes*> cartesMap;
  SDL_Renderer* Renderer;
  Node* currentMap;

 public:
  allMaps(SDL_Renderer* Renderer, donjon* Don);
  ~allMaps();
  void InitializeRoom(Player* player, world* Monde, std::string SpawnType);
  Cartes* getMap(char i);
  int getMapsSize();
  void InitializeLevel();
  void drawMap(SDL_Renderer* Renderer, int dx, int dy);
  int getMapWidth();
  int getMapHeight();
  Node* getCurrentMap();
  std::vector<tmx::Object> getCollisions();
  std::vector<tmx::Object> getElements();
  void InitializeAllMap(Node* node);

  void changeMap(std::string, Player* player, world* Monde);
};

#endif