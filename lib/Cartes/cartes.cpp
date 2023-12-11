#include "cartes.hpp"

#include "../monster/monster.hpp"
#include "../utility/utility.hpp"

Cartes::Cartes(SDL_Renderer* Renderer, std::string file) {
  this->file = file;
  this->Renderer = Renderer;
  Map = new level(file);
  Map->load(this->file, Renderer);  // Load the map
  load = false;
  Collisions = Map->getObjectsByType("Collision");  // Get all the collisions objects
  Elements = Map->getObjectsByType("tp");           // Get all the elements objects

  ElementsToAdd = mergeVectors(Map->getObjectsByType("blocks"), Map->getObjectsByType("wall"));
  ElementsToAdd = mergeVectors(ElementsToAdd, Map->getObjectsByType("monster"));

  Spawn["Spawn"] = Map->getObjectByName("Spawn");
  Spawn["TL"] = Map->getObjectByNameAndType("TL", "Spawn");
  Spawn["TR"] = Map->getObjectByNameAndType("TR", "Spawn");
  Spawn["DL"] = Map->getObjectByNameAndType("DL", "Spawn");
  Spawn["DR"] = Map->getObjectByNameAndType("DR", "Spawn");
  player = nullptr;
}

Cartes::~Cartes() {
  delete Map;
  for(long unsigned int i = 0; i < addTiles.size(); i++) {
    delete addTiles[i];
  }
  for(long unsigned int i = 0; i < monsterList.size(); i++) {
    delete monsterList[i];
  }
}

void Cartes::draw(SDL_Renderer* Renderer) {
  Map->draw(Renderer, dx, dy);
  for(long unsigned int i = 0; i < addTiles.size(); i++) {
    addTiles[i]->draw(Renderer, dx, dy);
  }

  for(long unsigned int i2 = 0; i2 < monsterList.size(); i2++) {
    monsterList.at(i2)->Image.selfDraw(Renderer, monsterList.at(i2)->getRX() - dx, monsterList.at(i2)->getRY() - dy);
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

int Cartes::getDx() { return dx; }

int Cartes::getDy() { return dy; }

void Cartes::update(Uint32 currentTime, int dx, int dy) {
  this->dx = dx;
  this->dy = dy;
  for(long unsigned int i = 0; i < monsterList.size(); i++) {
    monsterList.at(i)->applyGravity();
    monsterList.at(i)->ai(dx, dy);
    monsterList.at(i)->update(currentTime);
    if(player->isCollidingEntity(monsterList.at(i))) {
      player->takeDamage(1);
      player->knockback(monsterList.at(i));
    }
  }
}

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
    cartesMap[this->currentMap->getValue()]->setLoad(true);
    for(tmx::Object c : cartesMap[this->currentMap->getValue()]->getElementsToAdd()) {
      if(c.getClass() == "blocks") {
        if(getPropertyFromName(c.getProperties(), "typefile").getStringValue() == "image") {
          Tile* tile = new Tile(Renderer, getPropertyFromName(c.getProperties(), "file").getFileValue().substr(9), c.getPosition().x, c.getPosition().y, c.getAABB().width,
                                c.getAABB().height);
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
            cartesMap[this->currentMap->getValue()]->addTile(tile);
          }
          if(getPropertyFromName(c.getProperties(), "collision").getBoolValue()) {
            cartesMap[this->currentMap->getValue()]->addCollision(c);
          }
        }
      } else if(c.getClass() == "monster") {
        monster* monstre = new monster(Renderer);
        monstre->InitMonster(getCollisions());
        monstre->AllMove(c.getPosition().x, c.getPosition().y, true);
        cartesMap[this->currentMap->getValue()]->monsterList.push_back(monstre);
      }
    }
  }
  this->cartesMap[this->currentMap->getValue()]->player = player;
  player->InitPlayer(getCollisions(), &cartesMap[this->currentMap->getValue()]->monsterList);
  player->AllMove(object.getPosition().x, object.getPosition().y, true);
  Monde->FixCamera();
}

allMaps::~allMaps() {
  for(auto map : cartesMap) {
    delete map.second;
  }
  if(currentMap != nullptr) {
    delete currentMap;
  }
}

void allMaps::drawMap(SDL_Renderer* Renderer) { this->cartesMap[this->currentMap->getValue()]->draw(Renderer); }

Cartes* allMaps::getMap(char i) { return cartesMap[i]; }

int allMaps::getMapsSize() { return cartesMap.size(); }

int allMaps::getMapWidth() { return cartesMap[this->currentMap->getValue()]->getMap()->getMapWidth(); }

int allMaps::getMapHeight() { return cartesMap[this->currentMap->getValue()]->getMap()->getMapHeight(); }

Node* allMaps::getCurrentMap() { return this->currentMap; }

std::vector<tmx::Object> allMaps::getCollisions() { return cartesMap[this->currentMap->getValue()]->getCollisions(); }

std::vector<tmx::Object> allMaps::getElements() { return cartesMap[this->currentMap->getValue()]->getElements(); }

void allMaps::changeMap(std::string map, Player* player, world* Monde) {
  std::string SpawnType = "Spawn";
  if(map == "Spawn") {
    this->currentMap = this->Donjon->initial_Node;
    getCurrentMap()->getRoom()->SetInTheRoom(true);
  } else {
    Node* oldNode = getCurrentMap();
    getCurrentMap()->getRoom()->SetInTheRoom(false);

    this->currentMap = Donjon->getElementInChildFromPlacement(map, getCurrentMap());

    SpawnType = Donjon->getAdjacentTypeFromNode(getCurrentMap(), oldNode);

    getCurrentMap()->getRoom()->SetInTheRoom(true);
  }
  InitializeRoom(player, Monde, SpawnType);
}

void allMaps::update(Uint32 currentTime, int dx, int dy) { cartesMap[this->currentMap->getValue()]->update(currentTime, dx, dy); }

int allMaps::getDx() { return cartesMap[this->currentMap->getValue()]->getDx(); }

int allMaps::getDy() { return cartesMap[this->currentMap->getValue()]->getDy(); }
