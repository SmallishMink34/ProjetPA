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
  tmx::Object Spawn;
  std::vector<tmx::Object> Elements;

 public:
  Cartes(SDL_Renderer* Renderer, std::string file);
  ~Cartes();
  level* getMap();
  void draw(SDL_Renderer* Renderer, int dx, int dy);
  std::vector<tmx::Object> getCollisions();
  std::vector<tmx::Object> getElements();
  tmx::Object getSpawn();
};

class allMaps {
 private:
  donjon* Donjon;
  std::map<std::string, Cartes*> cartesMap;
  SDL_Renderer* Renderer;
  std::string currentMap;

 public:
  allMaps(SDL_Renderer* Renderer);
  ~allMaps();
  void InitializeRoom(Player* player, world* Monde);
  Cartes* getMap(std::string i);
  int getMapsSize();
  void InitializeLevel();
  void drawMap(SDL_Renderer* Renderer, int dx, int dy);
  int getMapWidth();
  int getMapHeight();
  std::vector<tmx::Object> getCollisions();
  std::vector<tmx::Object> getElements();

  void changeMap(std::string map, Player* player, world* Monde);
};

#endif