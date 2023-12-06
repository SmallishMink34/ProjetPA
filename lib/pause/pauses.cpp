#include "pauses.hpp"

#include "../gamemode/gamemode.hpp"
#include "../utility/utility.hpp"
#include <SDL2/SDL_ttf.h>
// #include "../button/button.cpp"

Mpause::Mpause(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var) {
  this->gWindow = gWindow;
  this->gRenderer = gRenderer;
  quit = false;
  isLoaded = false;
  this->Var = Var;

  var = false;
}

void Mpause::Init() {
  isLoaded = true;
  Var->ChangeScale(1);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);

  this->Image = Sprite("src/Images/pause.png", 0, 0, Var->Real_W, Var->Real_H);
  Image.loadImage(gRenderer);

  // bouton play
  this->play = Bouton(gRenderer, "src/Images/play.png", Var->Real_W / 2 - 135, Var->Real_H / 3, 256, 128);
  this->play.setSurface(0, 0, 512, 256);
  this->play.gererPlay(&evenement, gRenderer, &var);

  // bouton exit
  this->exit = Bouton(gRenderer, "src/Images/exit.png", Var->Real_W - 180, Var->Real_H - 90, 192, 96);
  this->exit.setSurface(0, 256, 512, 256);
  this->exit.gererFin(&evenement, gRenderer, &quit);

  // afficher le mot "pause" en haut   
  TTF_Font* Sans = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  SDL_Color Blue = {0, 191, 255};

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Pause", Blue);  
  TextureMessage = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); 
  Message_rect;                                                             
  Message_rect.x = Var->Real_W / 2 - 50;                                    
  Message_rect.y = 13;                                                      
  Message_rect.w = 120;                                                     
  Message_rect.h = 60;     

  std::string seed = std::to_string(getSeedFromFile("map.txt"));
  int taille = compterLettres(seed);
  std::cout << taille << std::endl;

  SDL_Color White = {255, 255, 255};
  SDL_Surface* surfaceSeed = TTF_RenderText_Solid(Sans, seed.c_str(), White);
  TextureSeed = SDL_CreateTextureFromSurface(gRenderer, surfaceSeed);
  Seed_rect;
  Seed_rect.x = 80-80/2;
  Seed_rect.y = Var->Real_H - 59;
  Seed_rect.w = 80;
  Seed_rect.h = 40;
  std::cout << "seed : " << seed << std::endl;
}
void Mpause::handleEvents(std::string* Gamemode) {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    exit.gererFin(&e, this->gRenderer, &quit);
    play.gererPlay(&e, this->gRenderer, &var);
    if(var) {
      *Gamemode = "jeu";
      var = false;
    }
    if(e.type == SDL_QUIT) {
      quit = true;
    } else if(e.type == SDL_KEYDOWN) {
      // Vérifiez quelle touche a été enfoncée
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
          *Gamemode = "jeu";
          var = false;
          break;
      }
    }

    // Appeler la fonction de gestion des événements du bouton
  }
}

void Mpause::render() {
  // Efface le renderer
  SDL_RenderClear(gRenderer);
  Image.selfDraw(gRenderer);
  exit.selfDraw(gRenderer);
  SDL_RenderCopy(gRenderer, TextureSeed, NULL, &Seed_rect);
  SDL_RenderCopy(gRenderer, TextureMessage, NULL, &Message_rect); 
  //play.selfDraw(gRenderer);
  // Met à jour le renderer
  SDL_RenderPresent(gRenderer);
}

void Mpause::update() {}

void Mpause::unpause() {
  Var->ChangeScale(1);
  SDL_RenderSetScale(this->gRenderer, Var->scale, Var->scale);  // Faire un zoom dans la fenetre
  SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
}