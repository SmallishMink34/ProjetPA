#ifndef DefHude
#define DefHude
#include <SDL2/SDL.h>

#include <iostream>

#include "../donjon/donjon.hpp"
#include "../player/player.hpp"
#include "../sprites/sprite.hpp"
/**
 * @class HUD
 * @brief Represents the Heads-Up Display (HUD) in the game.
 *
 * The HUD class is responsible for displaying the player's health, map frame, and other relevant information on the screen.
 */
class HUD {
 private:
  Player *Joueur;
  Sprite *vieEntiere;
  Sprite *vieDemi;
  Sprite *MapFrame;
  donjon *Don;
  SDL_Rect *rect;

  Variable *Var;
  SDL_Texture *TextureScore;
  SDL_Rect Score_rect;

  TTF_Font* Sans = TTF_OpenFont("src/font/Misty Style.ttf", 24);
  SDL_Color Blue = {0, 191, 255};

 public:
  /**
   * @brief Constructs a new HUD object.
   *
   * @param renderer The SDL renderer used for rendering the HUD.
   * @param Joueur A pointer to the Player object.
   * @param Don A pointer to the donjon object.
   */
  HUD(SDL_Renderer *renderer, Player *Joueur, donjon *Don);

  /**
   * @brief Destroys the HUD object and frees any allocated resources.
   */
  ~HUD();

  /**
   * @brief Draws the HUD on the screen.
   *
   * @param renderer The SDL renderer used for rendering the HUD.
   */
  void draw(SDL_Renderer *renderer);
  void update(SDL_Renderer* renderer);
  char scoreText[20];

};
#endif