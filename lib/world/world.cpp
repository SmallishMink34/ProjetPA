#include "world.hpp"

#include "../../Constante.hpp"
#include "../donjon/donjon.hpp"

world::world(SDL_Renderer *Renderer) {
  this->Map = new level("map");
  this->Joueur = new Player(Renderer);
  this->AllElements = Texture();
  this->currentTime = SDL_GetTicks();
  this->deltaTime = this->currentTime;
  this->previousTime = 0;
  this->dx = 0;
  this->dy = 0;
  this->seeMap = false;
}

void world::UpdateAll() {
  this->currentTime = SDL_GetTicks();
  this->deltaTime = (this->currentTime - this->previousTime) / 10.0;
  // affichage du temps
  this->previousTime = this->currentTime;
  this->movePlayer();
  this->moveCamera();
}

void world::moveCamera() {
  // Récupérer les coordonnées du joueur
  int playerX = Joueur->getRX();
  int playerY = Joueur->getRY();

  // Calculer le décalage horizontal et vertical de la caméra pour centrer le
  // joueur
  float targetCameraX = playerX - (Real_W / 2);
  float targetCameraY = playerY - (Real_H / 2);

  if(targetCameraX < 0) {
    targetCameraX = 0;
  } else if(targetCameraX > Map->getMapWidth() - Real_W) {
    targetCameraX = Map->getMapWidth() - Real_W;
  }

  if(targetCameraY < 0) {
    targetCameraY = 0;
  } else if(targetCameraY > Map->getMapHeight() - Real_H) {
    targetCameraY = Map->getMapHeight() - Real_H;
  }

  // Appliquer l'interpolation pour déplacer progressivement la caméra
  dx += (targetCameraX - dx) * CameraSpeed;
  dy += (targetCameraY - dy) * CameraSpeed;
}

void world::movePlayer() {
  // Appliquer la gravité
  this->Joueur->applyGravity(this->deltaTime);

  int moveX = 0;
  int moveY = 0;
  // Gérer les mouvements verticaux (haut / bas)
  if(this->KeyPressed[2] && this->Joueur->isOnGround()) {
    this->Joueur->jump();
  }

  // Gérer les déplacements horizontaux
  if(this->KeyPressed[0]) {
    moveX = -this->Joueur->speed;
  }
  if(this->KeyPressed[1]) {
    moveX = this->Joueur->speed;
  }
  if(this->KeyPressed[3]) {
    moveY = this->Joueur->speed;
  }

  this->Joueur->Move(moveX * this->deltaTime, moveY);
}

void world::InitMonde(SDL_Renderer *Renderer) {
  this->AllElements.addElements(Renderer, Sprite("src/Images/image.jpg", 0, 420, 1280, 720));

  this->Map->load("Maps/Map2.tmx", Renderer);

  tmx::Object object = this->Map->getObjectByName("Spawn");
  Collisions = this->Map->getObjectsByType("Collision");

  this->Joueur->InitPlayer(Collisions, this);
  this->Joueur->AllMove(object.getPosition().x, object.getPosition().y, true);
  this->Joueur->FixCamera();
}

void world::drawAll(SDL_Renderer *Renderer) {
  this->Map->draw(Renderer, dx, dy);
  // this->AllElements.drawElements(Renderer);
  this->Joueur->Image.selfDraw(Renderer);

  drawMap(Renderer);
}

void world::newDonjon() {
  this->Donjon = new donjon(30, 0);
  // this->Donjon->create_tree();

  // this->Donjon->save_rooms_to_file(this->Donjon->initial_Node);
  this->Donjon->load_rooms_from_file();
  this->Donjon->drawDungeon(this->Donjon->initial_Node);
  this->seeMap = true;
}

void world::drawMap(SDL_Renderer *Renderer) {
  if(seeMap) {
    this->Donjon->draw_tree(Renderer, this->Donjon->initial_Node);
  }
}