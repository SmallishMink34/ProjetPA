#include "world.hpp"
#include "../../Constante.hpp"

world::world(SDL_Renderer* Renderer, int Real_W, int Real_H){
    this->Map = new level("map");
    this->Joueur = new Player(Renderer);
    this->AllElements = Texture();
    this->currentTime  = SDL_GetTicks();
    this->deltaTime = this->currentTime;
    this->previousTime = 0;
    this->Animcpt = 0;
    this->cptest = 0;
    this->dx = 0;
    this->dy = 0;
    this->Real_W = Real_W;
    this->Real_H = Real_H;
}

void world::UpdateAll(){
    this->currentTime = SDL_GetTicks();
    this->deltaTime = (this->currentTime - this->previousTime)/10.0;
    // affichage du temps
    this->previousTime = this->currentTime;
    this->movePlayer();
    this->moveCamera();

    
    this->cptest++;
    
    if (cptest%10 == 0){
        this->Animcpt++;
        if (Animcpt > Joueur->etats[Joueur->etat].size()-1){
            Animcpt = 0;
        }
        this->Joueur->AnimPlayer(Animcpt);
    }

}
 
void world::moveCamera() {
    // Récupérer les coordonnées du joueur
    int playerX = Joueur->getRX();
    int playerY = Joueur->getRY();

    // Calculer le décalage horizontal et vertical de la caméra pour centrer le joueur
    float targetCameraX = playerX - (Real_W / 2);
    float targetCameraY = playerY - (Real_H / 2);

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
    // Gérer les mouvements verticaux (haut / bas)
    if (this->KeyPressed[2] && this->Joueur->isOnGround()) {
        this->Joueur->jump();
        this->Joueur->etat = "Jump";
        //printf("etat : %s\n", this->Joueur->etat.c_str());
        //printf("etat : %d %d\n", this->Joueur->etats[this->Joueur->etat][0].first, this->Joueur->etats[this->Joueur->etat][0].second);
    }
    // Gérer les déplacements horizontaux
    if (this->KeyPressed[0]) {
        this->Joueur->Move(-(this->Joueur->speed) * this->deltaTime, 0);
        this->Joueur->etat = "Left";
        //printf("etat : %s\n", this->Joueur->etat.c_str());
    }
    if (this->KeyPressed[1]) {
        this->Joueur->Move(this->Joueur->speed * this->deltaTime, 0);
        this->Joueur->etat = "Right";
        //printf("etat : %s\n", this->Joueur->etat.c_str());
    }

    if (this->KeyPressed[3]) {
        if (this->Joueur->isOnGround()) {
            this->Joueur->Move(0, this->Joueur->speed * this->deltaTime);
            this->Joueur->etat = "Idle";
        }
        //printf("etat : %s\n", this->Joueur->etat.c_str());
    }
    
}

void world::InitMonde(SDL_Renderer* Renderer){

    this->AllElements.addElements(Renderer, Sprite("src/Images/image.jpg", 0, 420, 1280, 720));
    
    this->Map->load("Maps/Map2.tmx", Renderer);
    
    tmx::Object object = this->Map->getObjectByName("Spawn");
    Collisions = this->Map->getObjectsByType("Collision");
    this->Joueur->InitPlayer(Collisions, this);
    this->Joueur->AllMove(object.getPosition().x, object.getPosition().y, true);
    this->Joueur->FixCamera(int (this->Real_W), int (this->Real_H));
}

void world::drawAll(SDL_Renderer* Renderer){
    this->Map->draw(Renderer, dx, dy);
    //this->AllElements.drawElements(Renderer);
    this->Joueur->Image.selfDraw(Renderer);
}