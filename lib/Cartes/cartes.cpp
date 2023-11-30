#include "cartes.hpp"

Cartes::Cartes(SDL_Renderer* Renderer, std::string file) {
  this->file = file;
  this->Renderer = Renderer;
  Map = new level(file);
  Map->load(this->file, Renderer);        // Load the map
  Spawn = Map->getObjectByName("Spawn");  // Get the spawn object

  Collisions = Map->getObjectsByType("Collision");  // Get all the collisions objects

  Elements = Map->getObjects();  // Get all the elements objects
}

Cartes::~Cartes() { delete Map; }

void Cartes::draw(SDL_Renderer* Renderer, int dx, int dy) { Map->draw(Renderer, dx, dy); }

level* Cartes::getMap() { return Map; }

std::vector<tmx::Object> Cartes::getCollisions() { return Collisions; }

std::vector<tmx::Object> Cartes::getElements() { return Elements; }

tmx::Object Cartes::getSpawn() { return Spawn; }
////////////////////////////////// allMaps //////////////////////////////////

allMaps::allMaps(SDL_Renderer* Renderer) {
  this->Renderer = Renderer;

  this->currentMap = "spawn";

  this->cartesMap["spawn"] = new Cartes(Renderer, "Maps/tmx/Spawn.tmx");

  this->cartesMap["1"] = new Cartes(Renderer, "Maps/Map2.tmx");
}

void allMaps::InitializeLevel() { this->Donjon = new donjon(30, 0); }

void allMaps::InitializeRoom(Player* player, world* Monde) {
  tmx::Object object = cartesMap[this->currentMap]->getSpawn();

  player->InitPlayer(getCollisions(), Monde);
  player->AllMove(object.getPosition().x, object.getPosition().y, true);
  player->FixCamera();
}

allMaps::~allMaps() {
  for(auto map : cartesMap) {
    delete map.second;
  }
}

void allMaps::drawMap(SDL_Renderer* Renderer, int dx, int dy) { this->cartesMap[this->currentMap]->draw(Renderer, dx, dy); }

Cartes* allMaps::getMap(std::string i) { return cartesMap[i]; }

int allMaps::getMapsSize() { return cartesMap.size(); }

int allMaps::getMapWidth() { return cartesMap[this->currentMap]->getMap()->getMapWidth(); }

int allMaps::getMapHeight() { return cartesMap[this->currentMap]->getMap()->getMapHeight(); }

std::vector<tmx::Object> allMaps::getCollisions() { return cartesMap[this->currentMap]->getCollisions(); }

std::vector<tmx::Object> allMaps::getElements() { return cartesMap[this->currentMap]->getElements(); }

void allMaps::changeMap(std::string map, Player* player, world* Monde) {
  this->currentMap = map;
  InitializeRoom(player, Monde);
}