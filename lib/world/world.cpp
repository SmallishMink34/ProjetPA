#include "world.hpp"
#include "../../Constante.cpp"

world::world(SDL_Renderer* Renderer){
    this->Map = new level("map");
    this->Joueur = new Player(Renderer);
    this->AllElements = Texture();
    this->currentTime  = SDL_GetTicks();
    this->deltaTime = this->currentTime;
    this->previousTime = 0;
    
}

void world::UpdateAll(){
    this->currentTime  = SDL_GetTicks();
    this->deltaTime = (this->currentTime - this->previousTime)/10.0;
    // affichage du temps
    this->previousTime = this->currentTime;
    this->movePlayer();
}

void world::movePlayer(){
    this->Joueur->Move(0, Gravity*this->deltaTime); 

    if(this->KeyPressed[0]){
        this->Joueur->Move(-(this->Joueur->speed)*this->deltaTime , 0);
    }
    if(this->KeyPressed[1]){
        this->Joueur->Move(this->Joueur->speed*this->deltaTime , 0);
    }
}

void world::InitMonde(SDL_Renderer* Renderer){
    this->AllElements.addElements(Renderer, Sprite("src/Images/image.jpg", 0, 420, 1280, 720));
    this->Map->load("Maps/Map.tmx", Renderer);
}

void world::drawAll(SDL_Renderer* Renderer){
    
    this->Map->draw(Renderer);
    this->AllElements.drawElements(Renderer);
    this->Joueur->Image.selfDraw(Renderer);
    

}