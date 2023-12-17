#include "world.hpp"

#include "../donjon/donjon.hpp"
#include "../donjon/tree.hpp"

world::world(SDL_Renderer* Renderer, Variable* Var) {
  this->Donjon = new donjon(30, 5);
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

int world::getScore() { return this->Joueur->getScore() / 120; }

world::~world() {
  delete this->Joueur;
  delete this->Donjon;
  delete this->Map;
  delete this->hud;
}

bool world::EndGame() {
  if(((this->Donjon->getNbMonsterAllMap(this->Donjon->initial_Node) == 0 && this->Donjon->allNodeVisited(this->Donjon->initial_Node)) || this->Joueur->getVie() <= 0) && genWorld) {
    return true;
  } else {
    return false;
  }
}