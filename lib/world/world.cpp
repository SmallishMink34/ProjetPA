#include "world.hpp"

#include "../donjon/donjon.hpp"
#include "../donjon/tree.hpp"

world::world(SDL_Renderer* Renderer, Variable* Var) {
  this->Donjon = new donjon(30, Renderer);
  this->Map = new allMaps(Renderer, this->Donjon);
  this->Joueur = new Player(Renderer);
  this->hud = new HUD(Renderer, this->Joueur, this->Donjon, Var);

  this->currentTime = SDL_GetTicks();
  this->deltaTime = this->currentTime;
  this->previousTime = 0;
  this->cptest = 0;

  this->dx = 0;
  this->dy = 0;
  this->Var = Var;
  this->seeMap = false;

  this->genWorld = false;
  this->canQuitWorld = false;
  this->doorIsRemoved = false;
}

void world::InitMonde(SDL_Renderer* Renderer) { Map->InitializeRoom(this->Joueur, this, "Spawn"); }

int world::UpdateAll() {
  this->currentTime = SDL_GetTicks();
  this->deltaTime = (this->currentTime - this->previousTime) / 10.0;
  this->previousTime = this->currentTime;
  this->movePlayer();

  this->Map->update(currentTime, dx, dy);
  this->Joueur->update(currentTime);

  this->Joueur->Arme->update();

  tmx::Object collision = this->Joueur->isColliding(this->Map->getElements());
  std::string collisionType = collision.getType();

  tmx::Object Element = this->Joueur->isColliding(this->Map->getInteract());
  std::string elementType = Element.getType();

  if(collisionType == "tp") {
    std::string whatDoor = collision.getName();
    if(whatDoor == "Spawn") {
      if(this->Map->InitializeLevel() == -1) {
        return -1;
      }
      this->seeMap = true;
    } else {
      genWorld = true;
    }
    Var->CameraSpeed = 1;
    this->Joueur->setVerticalVelocity(0);
    this->Map->changeMap(whatDoor, this->Joueur, this);
  } else if(elementType == "end") {
    this->canQuitWorld = true;
  } else {
    this->canQuitWorld = false;
  }

  if(OpenTheDoor() && this->Map->getCurrentMap()->getRoom()->getIsEnd() && !doorIsRemoved) {  // Tenter d'enlever la porte qu'une seule fois
    this->Map->removeTile("close");
    doorIsRemoved = true;
  }

  this->moveCamera();
  Var->CameraSpeed = Var->DefaultCameraSpeed;
  this->cptest++;

  this->Joueur->AnimEntity(cptest);
  return 0;
}

void world::moveCamera() {
  // Récupérer les coordonnées du joueur
  int playerX = Joueur->getRX();
  int playerY = Joueur->getRY();

  // Calculer le décalage horizontal et vertical de la caméra pour centrer le joueur
  float targetCameraX = playerX - (Var->Real_W / 2);
  float targetCameraY = playerY - (Var->Real_H / 2);

  if(targetCameraX < 0) {
    targetCameraX = 0;
  } else if(targetCameraX > Map->getMapWidth() - Var->Real_W) {
    targetCameraX = Map->getMapWidth() - Var->Real_W;
  }
  if(targetCameraX < 0) {
    targetCameraX = 0;
  } else if(targetCameraX > Map->getMapWidth() - Var->Real_W) {
    targetCameraX = Map->getMapWidth() - Var->Real_W;
  }

  if(targetCameraY < 0) {
    targetCameraY = 0;
  } else if(targetCameraY > Map->getMapHeight() - Var->Real_H) {
    targetCameraY = Map->getMapHeight() - Var->Real_H;
  }

  // Appliquer l'interpolation pour déplacé progressivement la caméra
  dx += (targetCameraX - dx) * Var->CameraSpeed;
  dy += (targetCameraY - dy) * Var->CameraSpeed;
}

void world::movePlayer() { this->Joueur->selfMove(this->KeyPressed, this->mouseX, this->mouseY, dx, dy); }

void world::drawMap(SDL_Renderer* Renderer) {
  if(seeMap) {
    this->hud->draw(Renderer);
  }
}

void world::drawAll(SDL_Renderer* Renderer) {
  this->Map->drawMap(Renderer);
  this->Joueur->Image.selfDraw(Renderer);
  this->Joueur->Arme->draw(Renderer, dx, dy);

  drawMap(Renderer);
}

void world::FixCamera() {
  if(this->Joueur->getX() > Map->getMapWidth() - Var->Real_W / 2) {
    int nombre = Map->getMapWidth() - Var->Real_W;
    this->Joueur->setX(this->Joueur->getX() - nombre);
  }
  if(this->Joueur->getY() > Map->getMapHeight() - Var->Real_H / 2) {
    int nombre = Map->getMapHeight() - Var->Real_H;
    this->Joueur->setY(this->Joueur->getY() - nombre);
  }
  this->Joueur->Moveto();
}

int world::getScore() { return this->Joueur->getScore() / scoreDivider; }

world::~world() {
  delete this->Joueur;
  std::cout << "Player deleted" << std::endl;
  delete this->Map;

  delete this->hud;
  std::cout << "HUD deleted" << std::endl;
  delete this->Donjon;
  std::cout << "Map deleted" << std::endl;
}

bool world::OpenTheDoor() {
  return (((this->Donjon->getNbMonsterAllMap(this->Donjon->initial_Node) == 0 && this->Donjon->allNodeVisited(this->Donjon->initial_Node))) && genWorld);
}

bool world::EndGame() {
  if((canQuitWorld && OpenTheDoor()) || this->Joueur->getVie() <= 0) {
    return true;
  } else {
    return false;
  }
}