#include "world.hpp"
#include "../../Constante.hpp"

world::world(SDL_Renderer* Renderer){
    this->Map = new level("map");
    this->Joueur = new Player(Renderer);
    this->AllElements = Texture();
    this->currentTime  = SDL_GetTicks();
    this->deltaTime = this->currentTime;
    this->previousTime = 0;
    this->dx = 0;
    this->dy = 0;
}

void world::UpdateAll(){
    this->currentTime  = SDL_GetTicks();
    this->deltaTime = (this->currentTime - this->previousTime)/10.0;
    // affichage du temps
    this->previousTime = this->currentTime;
    this->movePlayer();
    this->moveCamera();
}
 
void world::moveCamera() {
    // Récupérer les coordonnées du joueur
    int playerX = Joueur->getX();
    int playerY = Joueur->getY();

    // Calculer le décalage horizontal et vertical de la caméra pour centrer le joueur
    float targetCameraX = playerX - (Real_W / 2);
    float targetCameraY = playerY - (Real_H / 2);

    // Assurez-vous que la caméra ne dépasse pas les bords de la carte
    if (targetCameraX < 0) {
        targetCameraX = 0;
    } else if (targetCameraX > Map->getMapWidth() - Real_W) {
        targetCameraX = Map->getMapWidth() - Real_W;
    }

    if (targetCameraY < 0) {
        targetCameraY = 0;
    } else if (targetCameraY > Map->getMapHeight() - Real_H) {
        targetCameraY = Map->getMapHeight() - Real_H;
    }

    // Appliquer l'interpolation pour déplacer progressivement la caméra
    dx += (targetCameraX - dx) * CameraSpeed;
    dy += (targetCameraY - dy) * CameraSpeed;
}



void world::movePlayer() {
    // Appliquer la gravité
    this->Joueur->applyGravity(this->deltaTime);

        // Gérer les mouvements verticaux (haut et bas)
    if (this->KeyPressed[2] && this->Joueur->isOnGround()) {
        this->Joueur->jump();
    }
    // Gérer les déplacements horizontaux
    if (this->KeyPressed[0]) {
        this->Joueur->Move(-(this->Joueur->speed) * this->deltaTime, 0);
    }
    if (this->KeyPressed[1]) {
        this->Joueur->Move(this->Joueur->speed * this->deltaTime, 0);
    }


    if (this->KeyPressed[3]) {
        this->Joueur->Move(0, this->Joueur->speed * this->deltaTime);
    }
    
}

void world::InitMonde(SDL_Renderer* Renderer){

    this->AllElements.addElements(Renderer, Sprite("src/Images/image.jpg", 0, 420, 1280, 720));
    
    this->Map->load("Maps/Map2.tmx", Renderer);
    
    tmx::Object object = this->Map->getObjectByName("Spawn");
    Collisions = this->Map->getObjectsByType("Collision");
    this->Joueur->InitPlayer(Collisions, this);

    this->Joueur->Moveto(object.getPosition().x, object.getPosition().y);
    this->Joueur->RealMoveto(object.getPosition().x, object.getPosition().y);
    this->Joueur->FixCamera();
}

void world::drawAll(SDL_Renderer* Renderer){
    
    this->Map->draw(Renderer, dx, dy);
    //this->AllElements.drawElements(Renderer);
    this->Joueur->Image.selfDraw(Renderer);
    

}