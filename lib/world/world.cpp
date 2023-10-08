#include "world.hpp"
#include "../../Constante.hpp"

world::world(SDL_Renderer* Renderer){
    this->Map = new level("map");
    this->Joueur = new Player(Renderer, Map);
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
    dx = (playerX - (Real_W / 2));
    dy = (playerY - (Real_H / 2));
    // Assurer que la caméra ne dépasse pas les bords de la carte
    if (dx < 0) {
        dx = 0;
    } else if (dx > Map->getMapWidth() - Real_W) {
        dx = Map->getMapWidth() - Real_W;
    }

    if (dy < 0) {
        dy = 0;
    } else if (dy > Map->getMapHeight() - Real_H) {
        dy = Map->getMapHeight() - Real_H;
    }

}


void world::movePlayer(){
    this->Joueur->Move(0, Gravity*this->deltaTime); 

    if(this->KeyPressed[0]){
        this->Joueur->Move(-(this->Joueur->speed)*this->deltaTime , 0);
    }
    if(this->KeyPressed[1]){
        this->Joueur->Move(this->Joueur->speed*this->deltaTime , 0);
    }
    if(this->KeyPressed[2]){
        this->Joueur->Move(0, -this->Joueur->speed*this->deltaTime);
    }
    if(this->KeyPressed[3]){
        this->Joueur->Move(0, this->Joueur->speed*this->deltaTime);
    }
}

void world::InitMonde(SDL_Renderer* Renderer){

    this->AllElements.addElements(Renderer, Sprite("src/Images/image.jpg", 0, 420, 1280, 720));
    
    this->Map->load("Maps/Map2.tmx", Renderer);
    
    tmx::Object object = this->Map->getObjectByName("Spawn");
    Collisions = this->Map->getObjectsByType("Collision");
    this->Joueur->InitPlayer(Collisions);

    this->Joueur->Moveto(object.getPosition().x, object.getPosition().y);
    this->Joueur->RealMoveto(object.getPosition().x, object.getPosition().y);
    this->Joueur->FixCamera();
}

void world::drawAll(SDL_Renderer* Renderer){
    
    this->Map->draw(Renderer, dx, dy);
    //this->AllElements.drawElements(Renderer);
    this->Joueur->Image.selfDraw(Renderer);
    

}