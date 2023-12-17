#ifndef DefCartes
#define DefCartes
#include <SDL2/SDL.h>

#include <cstdarg>
#include <iostream>
#include <map>
#include <string>

#include "../donjon/donjon.hpp"
#include "../maps/maps.hpp"
#include "../monster/monster.hpp"
#include "../player/player.hpp"
#include "../world/world.hpp"
#include "tile.hpp"
class Player;
class world;

/**
 * @class Cartes
 * @brief Represents a map with various elements and functionalities.
 */
class Cartes {
 private:
  SDL_Renderer* Renderer;                   /**< The SDL renderer used to render the map */
  std::string file;                         /**< The file path of the map */
  level* Map;                               /**< Pointer to the level object representing the map */
  std::vector<tmx::Object> Collisions;      /**< Vector of collision objects on the map */
  std::vector<tmx::Object> Interact;        /**< Vector of interaction objects on the map */
  std::vector<tmx::Object> ElementsToAdd;   /**< Vector of additional elements to be added to the map */
  std::map<std::string, tmx::Object> Spawn; /**< Map of spawn points on the map */
  std::vector<tmx::Object> Elements;        /**< Vector of elements on the map */
  std::vector<Tile*> addTiles;              /**< Vector of additional tiles to be added to the map */
  bool load;                                /**< Flag indicating whether the map has been loaded */
  int dx;                                   /**< The change in x-coordinate */
  int dy;                                   /**< The change in y-coordinate */
  int animeMCounter;

 public:
  /**
   * @brief Construct a new Cartes object
   * @param Renderer The SDL renderer used to render the map
   * @param file The file path of the map
   */
  Cartes(SDL_Renderer* Renderer, std::string file);

  /**
   * @brief Destroy the Cartes object
   */
  ~Cartes();

  Player* player; /**< Pointer to the player object */

  /**
   * @brief Get the Map object
   * @return Pointer to the level object representing the map
   */
  level* getMap();

  /**
   * @brief Draw the map on the screen
   * @param Renderer The SDL renderer used to render the map
   */
  void draw(SDL_Renderer* Renderer);

  /**
   * @brief Get the Nb Monster object
   * @return The number of monsters on the map
   */

  int getNbMonster();

  /**
   * @brief Get the Collisions object
   * @return Vector of collision objects on the map
   */
  std::vector<tmx::Object> getCollisions();

  /**
   * @brief Get the Elements object
   * @return Vector of elements on the map
   */
  std::vector<tmx::Object> getElements();

  /**
   * @brief Get the spawn object with the specified key
   * @param a The key of the spawn object
   * @return The spawn object with the specified key
   */
  tmx::Object getSpawn(std::string a);

  /**
   * @brief Get the ElementsToAdd object
   * @return Vector of additional elements to be added to the map
   */
  std::vector<tmx::Object> getElementsToAdd();

  /**
   * @brief Check if the map has been loaded
   * @return True if the map has been loaded, false otherwise
   */
  bool hasBeenLoaded();

  /**
   * @brief Set the load flag
   * @param val The value to set the load flag to
   */
  void setLoad(bool val);

  /**
   * @brief Add a tile to the map
   * @param tile The tile to be added
   */
  void addTile(Tile* tile);

  /**
   * @brief Add a collision object to the map
   * @param object The collision object to be added
   */
  void addCollision(tmx::Object object);

  /**
   * @brief Update the map based on the current time and change in coordinates
   * @param currentTime The current time
   * @param dx The change in x-coordinate
   * @param dy The change in y-coordinate
   */
  void update(Uint32 currentTime, int dx, int dy);

  /**
   * @brief Get the dx value
   * @return The change in x-coordinate
   */
  int getDx();

  /**
   * @brief Get the dy value
   * @return The change in y-coordinate
   */
  int getDy();

  int SearchTilebyName(std::string name);

  void removeTile(std::string name);

  /**
   * @brief add interaction on the map
   */
  void addInteract(tmx::Object object);

  std::vector<tmx::Object> getInteract(); /**< Vector of interaction objects on the map */
  std::vector<monster*> monsterList;      /**< Vector of monster objects on the map */
};

/**
 * @brief Class representing all the maps in the game.
 */
class allMaps {
 private:
  donjon* Donjon;                     // Pointer to the donjon object
  std::map<char, Cartes*> cartesMap;  // Map of Cartes objects
  SDL_Renderer* Renderer;             // Pointer to the SDL_Renderer object
  Node* currentMap;                   // Pointer to the current map node

 public:
  /**
   * @brief Constructor for the allMaps class.
   * @param Renderer Pointer to the SDL_Renderer object.
   * @param Don Pointer to the donjon object.
   */
  allMaps(SDL_Renderer* Renderer, donjon* Don);

  /**
   * @brief Destructor for the allMaps class.
   */
  ~allMaps();

  /**
   * @brief Initializes the room with the given parameters.
   * @param player Pointer to the Player object.
   * @param Monde Pointer to the world object.
   * @param SpawnType Type of spawn.
   */
  void InitializeRoom(Player* player, world* Monde, std::string SpawnType);

  /**
   * @brief Gets the Cartes object with the specified key.
   * @param i Key of the Cartes object.
   * @return Pointer to the Cartes object.
   */
  Cartes* getMap(char i);

  /**
   * @brief Gets the size of the cartesMap.
   * @return Size of the cartesMap.
   */
  int getMapsSize();

  /**
   * @brief Initializes the level.
   * @return 0 if the level was initialized successfully, 1 otherwise.
   */
  int InitializeLevel();

  /**
   * @brief Draws the map using the given SDL_Renderer object.
   * @param Renderer Pointer to the SDL_Renderer object.
   */
  void drawMap(SDL_Renderer* Renderer);

  /**
   * @brief Gets the width of the current map.
   * @return Width of the current map.
   */
  int getMapWidth();

  /**
   * @brief Gets the height of the current map.
   * @return Height of the current map.
   */
  int getMapHeight();

  /**
   * @brief Gets the x-coordinate offset of the current map.
   * @return X-coordinate offset of the current map.
   */
  int getDx();

  /**
   * @brief Gets the y-coordinate offset of the current map.
   * @return Y-coordinate offset of the current map.
   */
  int getDy();

  /**
   * @brief Gets the current map node.
   * @return Pointer to the current map node.
   */
  Node* getCurrentMap();

  /**
   * @brief Gets the collisions on the current map.
   * @return Vector of tmx::Object representing the collisions.
   */
  std::vector<tmx::Object> getCollisions();

  /**
   * @brief Gets the elements on the current map.
   * @return Vector of tmx::Object representing the elements.
   */
  std::vector<tmx::Object> getElements();

  /**
   * @brief Initializes all the maps using the given node.
   * @param node Pointer to the node representing the maps.
   */
  void InitializeAllMap(Node* node);

  /**
   * @brief Changes the current map to the one with the specified name.
   * @param name Name of the map to change to.
   * @param player Pointer to the Player object.
   * @param Monde Pointer to the world object.
   */
  void changeMap(std::string name, Player* player, world* Monde);

  /**
   * @brief Updates the allMaps object.
   * @param currentTime Current time in milliseconds.
   * @param dx X-coordinate offset.
   * @param dy Y-coordinate offset.
   */
  void update(Uint32 currentTime, int dx, int dy);

  /**
   * @brief get Interact object
   * @return Vector of tmx::Object representing the interactions.
   */
  std::vector<tmx::Object> getInteract();

  void removeTile(std::string name);
};

#endif