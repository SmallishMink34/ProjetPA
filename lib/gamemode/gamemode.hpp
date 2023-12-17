#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "../Variables/variables.hpp"
#include "../world/world.hpp"

/**
 * @class Gamemode
 * @brief Base class for game modes.
 *
 * This class represents a game mode in the game. It provides common functionality
 * and defines pure virtual functions that must be implemented by derived classes.
 */
class Gamemode {
 public:
  SDL_Window* gWindow;     /**< Pointer to the game window. */
  SDL_Renderer* gRenderer; /**< Pointer to the game renderer. */
  bool quit;               /**< Flag indicating if the game should quit. */
  bool isLoaded;           /**< Flag indicating if the game mode is loaded. */
  Variable* Var;           /**< Pointer to the game variables. */

  /**
   * @brief Default constructor for Gamemode.
   */
  Gamemode();

  /**
   * @brief Pure virtual function to handle events in the game mode.
   *
   * @param Gamemode A pointer to the current game mode.
   */
  virtual void handleEvents(std::string* Gamemode) = 0;

  /**
   * @brief Pure virtual function to initialize the game mode.
   */
  virtual bool Init() = 0;

  /**
   * @brief Pure virtual function to render the game mode.
   */
  virtual void render() = 0;

  /**
   * @brief Pure virtual function to update the game mode.
   */
  virtual int update() = 0;

  /**
   * @brief Pure virtual function to unpause the game mode.
   */
  virtual void unpause() = 0;

  /**
   * @brief Pure virtual destructor for Gamemode.
   */
  virtual ~Gamemode() = 0;
};

#endif