#ifndef pause_HPP
#define pause_HPP
#include <SDL2/SDL.h>

#include "../button/button.hpp"
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"

/**
 * @class Mpause
 * @brief Represents the pause menu gamemode.
 *
 * This class inherits from the Gamemode class and provides functionality for the pause menu.
 */
class Mpause: public Gamemode {
 public:
  /**
   * @brief Constructor for Mpause.
   * @param gWindow The SDL window.
   * @param gRenderer The SDL renderer.
   * @param Var A pointer to the Variable object.
   */
  Mpause(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);

  /**
   * @brief Destructor for Mpause.
   */
  ~Mpause();

  Sprite* Image;       /**< The image sprite. */
  Bouton* main_menu;   /**< The play button. */
  Bouton* exit;        /**< The exit button. */
  SDL_Event evenement; /**< The SDL event. */

  /**
   * @brief Initializes the pause menu.
   */
  void Init();

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
  void update();

  /**
   * @brief Unpauses the game.
   */
  void unpause();

  /**
   * @brief save the score text in a file
   */
  void saveScore();
  bool menu;
  int Real_W; /**< The real width. */
  int Real_H; /**< The real height. */

  SDL_Texture* TextureMessage;
  SDL_Rect Message_rect;
  SDL_Texture* TextureSeed;
  SDL_Rect Seed_rect;
  bool var; /**< The variable. */
};

#endif