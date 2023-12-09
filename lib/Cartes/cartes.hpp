#ifndef DefCartes
#define DefCartes
#include <SDL2/SDL.h>

#include <cstdarg>
#include <iostream>
#include <map>
#include <string>

#include "../donjon/donjon.hpp"
#include "../maps/maps.hpp"
#include "../monster/monster.hpp"
#include "../player/player.hpp"
#include "../world/world.hpp"
#include "tile.hpp"
class Player;
class world;
class Cartes {
 private:
  SDL_Renderer* Renderer;
  std::string file;
  level* Map;
  std::vector<tmx::Object> Collisions;
  std::vector<tmx::Object> ElementsToAdd;
  std::map<std::string, tmx::Object> Spawn;
  std::vector<tmx::Object> Elements;
  std::vector<Tile*> addTiles;
  bool load;
  int dx;
  int dy;

 public:
  Cartes(SDL_Renderer* Renderer, std::string file);
  ~Cartes();
  level* getMap();
  void draw(SDL_Renderer* Renderer);
  std::vector<tmx::Object> getCollisions();
  std::vector<tmx::Object> getElements();
  tmx::Object getSpawn(std::string a);
  std::vector<tmx::Object> getElementsToAdd();
  std::vector<monster*> monsterList;
  bool hasBeenLoaded();
  void setLoad(bool val);
  void addTile(Tile* tile);
  void addCollision(tmx::Object object);
  void update(Uint32 currentTime, int dx, int dy);
  int getDx();
  int getDy();
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
  void drawMap(SDL_Renderer* Renderer);
  int getMapWidth();
  int getMapHeight();
  int getDx();
  int getDy();
  Node* getCurrentMap();
  std::vector<tmx::Object> getCollisions();
  std::vector<tmx::Object> getElements();
  void InitializeAllMap(Node* node);

  void changeMap(std::string, Player* player, world* Monde);
  void update(Uint32 currentTime, int dx, int dy);
};

#endif