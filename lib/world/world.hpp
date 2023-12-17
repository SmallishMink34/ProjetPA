#ifndef DefWorld
#define DefWorld

#include "../Cartes/cartes.hpp"
#include "../HUD/hud.hpp"
#include "../Variables/variables.hpp"
#include "../display/display.hpp"
#include "../donjon/donjon.hpp"
#include "../maps/maps.hpp"
#include "../player/player.hpp"
#include "../weapon/armes.hpp"

class allMaps;
/**
 * @class world
 * @brief Represents the game world.
 *
 * The world class manages the game world, including the player, maps, HUD, and camera.
 * It provides functions for initializing the world, drawing all elements, moving the player,
 * updating all elements, moving the camera, fixing the camera, and drawing the map.
 */
class world {
 public:
  // Constucteur

  /**
   * @brief Constructs a world object.
   * @param Renderer The SDL renderer used for rendering.
   * @param Var A pointer to the Variable object.
   */
  world(SDL_Renderer* Renderer, Variable* Var);

  /**
   * @brief Destroys the world object.
   */
  ~world();

  // Variables
  Player* Joueur;                                           /**< The player object. */
  allMaps* Map;                                             /**< The map object. */
  HUD* hud;                                                 /**< The HUD object. */
  bool KeyPressed[5] = {false, false, false, false, false}; /**< An array representing the state of the keys (0 = left, 1 = right, 2 = up, 3 = down, 4 = click). */
  int dx;                                                   /**< The X offset of the map relative to the player. */
  int dy;                                                   /**< The Y offset of the map relative to the player. */
  int mouseX;                                               /**< The X coordinate of the mouse. */
  int mouseY;                                               /**< The Y coordinate of the mouse. */
  Variable* Var;                                            /**< A pointer to the Variable object. */
  donjon* Donjon;                                           /**< The donjon object. */
  bool seeMap;                                              /**< Flag indicating whether the map is visible. */
  Uint32 currentTime;                                       /**< The current time. */
  double deltaTime;                                         /**< The time elapsed since the previous frame. */
  Uint32 previousTime;                                      /**< The previous time. */
  Uint32 Animcpt;                                           /**< Animation counter. */
  Uint32 cptest;                                            /**< Test counter. */
  bool genWorld;                                            /**< Flag indicating whether the world has been generated. */

  // Fonctions
  /**
   * @brief Initializes the game world.
   * @param Renderer The SDL renderer used for rendering.
   */
  void InitMonde(SDL_Renderer* Renderer);

  /**
   * @brief Draws all elements in the game world.
   * @param Renderer The SDL renderer used for rendering.
   */
  void drawAll(SDL_Renderer* Renderer);

  /**
   * @brief Moves the player.
   */
  void movePlayer();

  /**
   * @brief Updates all elements in the game world.
   * @return 0 if the game is not ended, -1 if the game is ended by an error.
   */
  int UpdateAll();

  /**
   * @brief Moves the camera.
   */
  void moveCamera();

  /**
   * @brief Fixes the camera position.
   */
  void FixCamera();

  /**
   * @brief Draws the map.
   * @param Renderer The SDL renderer used for rendering.
   */
  void drawMap(SDL_Renderer* Renderer);

  /**
   * @brief get the score.
   */
  int getScore();

  /**
   * @brief return if the game is ended
   */
  bool EndGame();
};

#endif