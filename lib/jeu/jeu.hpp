#ifndef MENU_HPP
#define MENU_HPP

#include "../Variables/variables.hpp"
#include "../gamemode/gamemode.hpp"
#include "../world/world.hpp"

/**
 * @brief The Jeu class represents a game mode in the application.
 *
 * This class inherits from the Gamemode class and provides functionality
 * for initializing, pausing, handling events, rendering, updating, and
 * unpausing the game mode.
 */
class Jeu: public Gamemode {
 public:
  /**
   * @brief Constructs a new Jeu object.
   *
   * @param gWindow The SDL window used for rendering.
   * @param gRenderer The SDL renderer used for rendering.
   * @param Var A pointer to the Variable object.
   */
  Jeu(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);

  /**
   * @brief Destroys the Jeu object.
   */
  ~Jeu();

  /**
   * @brief Initializes the game mode.
   */
  void Init();

  /**
   * @brief Pauses the game mode.
   *
   * @param Gamemode A pointer to the current game mode.
   */
  void Pause(std::string* Gamemode);

  world* Monde;  // A pointer to the world object

  /**
   * @brief Handles events for the game mode.
   *
   * @param Gamemode A pointer to the current game mode.
   */
  void handleEvents(std::string* Gamemode);

  /**
   * @brief Renders the game mode.
   */
  void render();

  /**
   * @brief Updates the game mode.
   */
  void update();

  /**
   * @brief Unpauses the game mode.
   */
  void unpause();
};

#endif