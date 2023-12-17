#ifndef END_HPP
#define END_HPP
#include <SDL2/SDL.h>

#include "../button/button.hpp"
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"
#include "../texte/texte.hpp"

/**
 * @class Mpause
 * @brief Represents the pause menu gamemode.
 *
 * This class inherits from the Gamemode class and provides functionality for the pause menu.
 */
class END: public Gamemode {
 public:
  /**
   * @brief Constructor for Mpause.
   * @param gWindow The SDL window.
   * @param gRenderer The SDL renderer.
   * @param Var A pointer to the Variable object.
   */
  END(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);

  /**
   * @brief Destructor for Mpause.
   */
  ~END();

  Sprite* Image;       /**< The image sprite. */
  Bouton* main_menu;   /**< The play button. */
  Bouton* exit;        /**< The exit button. */
  SDL_Event evenement; /**< The SDL event. */
  texte* scoredialg;
  texte* scoreText;
  texte* info;
  texte* win;
  int score;

  /**
   * @brief Initializes the pause menu.
   * @return true if the pause menu was initialized successfully, false otherwise.
   */
  int Init();

  /**
   * @brief Handles events for the pause menu.
   * @param Gamemode A pointer to the current gamemode.
   */
  void handleEvents(std::string* Gamemode);

  /**
   * @brief Renders the pause menu.
   */
  void render();

  /**
   * @brief Updates the pause menu.
   */
  int update();

  /**
   * @brief Unpauses the game.
   */
  void unpause();

  /**
   * @brief save the score text in a file
   */
  bool menu;
  int Real_W; /**< The real width. */
  int Real_H; /**< The real height. */

  TTF_Font* Sans;
  SDL_Rect Message_rect;
  SDL_Rect Seed_rect;
  bool var; /**< The variable. */
};

#endif