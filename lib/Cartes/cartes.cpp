#include "cartes.hpp"

#include "../utility/utility.hpp"

Cartes::Cartes(SDL_Renderer* Renderer, std::string file) {
  this->file = file;
  this->Renderer = Renderer;
  Map = new level(file);
  Map->load(this->file, Renderer);  // Load the map
  load = false;
  Collisions = Map->getObjectsByType("Collision");  // Get all the collisions objects
  Elements = Map->getObjects();                     // Get all the elements objects

  ElementsToAdd = mergeVectors(Map->getObjectsByType("blocks"), Map->getObjectsByType("wall"));

  Spawn["Spawn"] = Map->getObjectByName("Spawn");
  Spawn["TL"] = Map->getObjectByNameAndType("TL", "Spawn");
  Spawn["TR"] = Map->getObjectByNameAndType("TR", "Spawn");
  Spawn["DL"] = Map->getObjectByNameAndType("DL", "Spawn");
  Spawn["DR"] = Map->getObjectByNameAndType("DR", "Spawn");
}

Cartes::~Cartes() { delete Map; }

void Cartes::draw(SDL_Renderer* Renderer, int dx, int dy) {
  Map->draw(Renderer, dx, dy);
  for(long unsigned int i = 0; i < addTiles.size(); i++) {
    addTiles[i]->draw(Renderer, dx, dy);
  }
}

level* Cartes::getMap() { return Map; }

std::vector<tmx::Object> Cartes::getCollisions() { return Collisions; }

std::vector<tmx::Object> Cartes::getElements() { return Elements; }

tmx::Object Cartes::getSpawn(std::string a) { return Spawn[a]; }

void Cartes::setLoad(bool val) { load = val; }

bool Cartes::hasBeenLoaded() { return load; }

std::vector<tmx::Object> Cartes::getElementsToAdd() { return ElementsToAdd; }

void Cartes::addTile(Tile* tile) { addTiles.push_back(tile); }

void Cartes::addCollision(tmx::Object object) { Collisions.push_back(object); }
////////////////////////////////// allMaps //////////////////////////////////

allMaps::allMaps(SDL_Renderer* Renderer, donjon* Don) {
  this->Renderer = Renderer;
  this->currentMap = new Node();
  this->Donjon = Don;

  this->cartesMap['0'] = new Cartes(Renderer, "Maps/tmx/Spawn.tmx");
}

void allMaps::InitializeAllMap(Node* node) {
  std::string map = node->getMap();

  if(node->getRoom()->getTall() == 1) {
    this->cartesMap[node->getValue()] = new Cartes(Renderer, "Maps/tmx/deux/" + map + ".tmx");
  } else {
    this->cartesMap[node->getValue()] = new Cartes(Renderer, "Maps/tmx/quatres/" + map + ".tmx");
  }

  if(node->getChildren().size() > 0) {
    for(std::pair<Node*, std::string> child : node->getChildren()) {
      InitializeAllMap(child.first);
    }
  }
}

void allMaps::InitializeLevel() {
  this->Donjon->load_rooms_from_file();

  InitializeAllMap(this->Donjon->initial_Node);
}

void allMaps::InitializeRoom(Player* player, world* Monde, std::string SpawnType) {
  tmx::Object object = cartesMap[this->currentMap->getValue()]->getSpawn(SpawnType);

  if(!cartesMap[this->currentMap->getValue()]->hasBeenLoaded()) {
    for(tmx::Object c : cartesMap[this->currentMap->getValue()]->getElementsToAdd()) {
      if(c.getClass() == "blocks") {
        if(getPropertyFromName(c.getProperties(), "typefile").getStringValue() == "image") {
          Tile* tile = new Tile(Renderer, getPropertyFromName(c.getProperties(), "file").getFileValue().substr(9), c.getPosition().x, c.getPosition().y, c.getAABB().width,
                                c.getAABB().height);
          std::cout << "Tile : " << getPropertyFromName(c.getProperties(), "file").getFileValue().substr(9) << " at " << c.getPosition().x << " " << c.getPosition().y << std::endl;
          cartesMap[this->currentMap->getValue()]->addTile(tile);
        }
        if(getPropertyFromName(c.getProperties(), "collision").getBoolValue()) {
          cartesMap[this->currentMap->getValue()]->addCollision(c);
        }
      } else if(c.getClass() == "wall") {
        if(!isInSecondVector(this->Donjon->getActualRoomNode(this->Donjon->initial_Node)->getChildAndParent(), c.getName())) {
          if(getPropertyFromName(c.getProperties(), "typefile").getStringValue() == "image") {
            Tile* tile = new Tile(Renderer, getPropertyFromName(c.getProperties(), "file").getFileValue().substr(9), c.getPosition().x, c.getPosition().y, c.getAABB().width,
                                  c.getAABB().height);
            std::cout << "Tile : " << getPropertyFromName(c.getProperties(), "file").getFileValue().substr(9) << " at " << c.getPosition().x << " " << c.getPosition().y
                      << std::endl;
            cartesMap[this->currentMap->getValue()]->addTile(tile);
          }
          if(getPropertyFromName(c.getProperties(), "collision").getBoolValue()) {
            cartesMap[this->currentMap->getValue()]->addCollision(c);
          }
        }
      }
    }
  }

  player->InitPlayer(getCollisions());
  player->AllMove(object.getPosition().x, object.getPosition().y, true);
  Monde->FixCamera();
}

allMaps::~allMaps() {
  for(auto map : cartesMap) {
    delete map.second;
  }
}

void allMaps::drawMap(SDL_Renderer* Renderer, int dx, int dy) { this->cartesMap[this->currentMap->getValue()]->draw(Renderer, dx, dy); }

Cartes* allMaps::getMap(char i) { return cartesMap[i]; }

int allMaps::getMapsSize() { return cartesMap.size(); }

int allMaps::getMapWidth() { return cartesMap[this->currentMap->getValue()]->getMap()->getMapWidth(); }

int allMaps::getMapHeight() { return cartesMap[this->currentMap->getValue()]->getMap()->getMapHeight(); }

Node* allMaps::getCurrentMap() { return this->currentMap; }

std::vector<tmx::Object> allMaps::getCollisions() { return cartesMap[this->currentMap->getValue()]->getCollisions(); }

std::vector<tmx::Object> allMaps::getElements() { return cartesMap[this->currentMap->getValue()]->getElements(); }

void allMaps::changeMap(std::string map, Player* player, world* Monde) {
  std::cout << "Change map : " << map << std::endl;
  std::string SpawnType = "Spawn";
  if(map == "Spawn") {
    this->currentMap = this->Donjon->initial_Node;
    getCurrentMap()->getRoom()->SetInTheRoom(true);
  } else {
    Node* oldNode = getCurrentMap();
    getCurrentMap()->getRoom()->SetInTheRoom(false);

    this->currentMap = Donjon->getElementInChildFromPlacement(map, getCurrentMap());

    SpawnType = Donjon->getAdjacentTypeFromNode(getCurrentMap(), oldNode);

    std::cout << "SpawnType : " << SpawnType << std::endl;
    getCurrentMap()->getRoom()->SetInTheRoom(true);
  }
  InitializeRoom(player, Monde, SpawnType);
}