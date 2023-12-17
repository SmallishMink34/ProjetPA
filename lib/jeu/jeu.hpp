#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL_mixer.h>

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
   * @return true if the game mode was initialized successfully, false otherwise.
   */
  bool Init();

  /**
   * @brief Pauses the game mode.
   *
   * @param Gamemode A pointer to the current game mode.
   */
  void Pause(std::string* Gamemode);

  /**
   * @brief Saves the score.
   */
  void saveScore();

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
   * @return 0 if the game mode was updated successfully, -1 if there was an error.
   */
  int update();

  /**
   * @brief Unpauses the game mode.
   */
  void unpause();

 private:
  Mix_Music* gameMusic;  // The background music
  Mix_Chunk* menuSound;  // The sound played when the game is paused
};

#endif