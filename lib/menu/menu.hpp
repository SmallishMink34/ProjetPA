#ifndef MENUE_HPP
#define MENUE_HPP
#include <SDL2/SDL.h>

#include "../button/button.hpp"
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"
#include "../texte/texte.hpp"

/**
 * @class menu
 * @brief Represents a menu gamemode.
 *
 * This class inherits from the Gamemode class and provides functionality for displaying and interacting with a menu.
 */
class menu: public Gamemode {
 public:
  /**
   * @brief Constructs a menu object.
   *
   * @param gWindow The SDL window to render on.
   * @param gRenderer The SDL renderer to use for rendering.
   * @param Var A pointer to a Variable object.
   */
  menu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);

  /**
   * @brief Destroys the menu object.
   */
  ~menu();

  Sprite* Image;       /**< The menu image sprite. */
  Sprite* titre;       /**< The menu title sprite. */
  Bouton* play;        /**< The play button. */
  Bouton* exit;        /**< The exit button. */
  SDL_Event evenement; /**< The SDL event object. */
  texte* scoredialg;
  texte* scoreText;

  /**
   * @brief Initializes the menu.
   */
  void Init();

  /**
   * @brief Handles events for the menu.
   *
   * @param Gamemode A pointer to a string representing the current gamemode.
   */
  void handleEvents(std::string* Gamemode);

  /**
   * @brief Renders the menu.
   */
  void render();

  /**
   * @brief Updates the menu.
   */
  void update();

  /**
   * @brief Unpauses the menu.
   */
  void unpause();

  int Real_W; /**< The real width of the menu. */
  int Real_H; /**< The real height of the menu. */
  bool var;   /**< A boolean variable. */
};

#endif