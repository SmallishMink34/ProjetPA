#pragma once

#include <cstdarg>
#include <map>
#include <string>
#include <vector>

#include "../sprites/sprite.hpp"
#include "SDL2/SDL.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/ObjectGroup.hpp"
typedef int gid;

// Stores information about an individual tile to be
// displayed.
struct tile {
  SDL_Texture* sheet;
  int x;
  int y;
  int tx;
  int ty;
  int width;
  int height;

  tile(SDL_Texture* tset, int x = 0, int y = 0, int tx = 0, int ty = 0, int w = 0, int h = 0);
  void draw(SDL_Renderer* ren, int dx, int dy);
};

/**
 * @brief Represents a level in the game.
 */
class level {
 public:
  /**
   * @brief Constructs a level object with the given name.
   *
   * @param name The name of the level.
   */
  level(const std::string& name);

  /**
   * @brief Loads the level from the specified path.
   *
   * @param path The path to the level file.
   * @param ren The SDL renderer used for rendering.
   */
  void load(const std::string& path, SDL_Renderer* ren);

  /**
   * @brief Draws the level on the specified renderer.
   *
   * @param ren The SDL renderer used for rendering.
   * @param dx The x-coordinate of the camera.
   * @param dy The y-coordinate of the camera.
   */
  void draw(SDL_Renderer* ren, int dx, int dy);

  /**
   * @brief Retrieves an object from the level by its name.
   *
   * @param Name The name of the object.
   * @return The object with the specified name.
   */
  tmx::Object getObjectByName(const std::string& Name);

  /**
   * @brief Retrieves all objects in the level.
   *
   * @return A vector containing all objects in the level.
   */
  std::vector<tmx::Object> getObjects();

  /**
   * @brief Retrieves all objects in the level with the specified type.
   *
   * @param Name The type of the objects.
   * @return A vector containing all objects with the specified type.
   */
  std::vector<tmx::Object> getObjectsByType(const std::string& Name);

  /**
   * @brief Retrieves an object from the level by its name and type.
   *
   * @param Name The name of the object.
   * @param Type The type of the object.
   * @return The object with the specified name and type.
   */
  tmx::Object getObjectByNameAndType(const std::string& Name, const std::string& Type);

  /**
   * @brief Gets the width of the level map.
   *
   * @return The width of the level map.
   */
  int getMapWidth();

  /**
   * @brief Gets the height of the level map.
   *
   * @return The height of the level map.
   */
  int getMapHeight();

 private:
  std::string name;                      // The name of the level.
  std::string tmxFilePath;               // The path to the level file.
  int rows;                              // The number of tiles from top to bottom (Y axis).
  int cols;                              // The number of tiles from left to right (X axis).
  int tile_width;                        // The width of each tile.
  int tile_height;                       // The height of each tile.
  std::vector<tile> tiles;               // The tiles to be drawn on the screen.
  std::map<gid, SDL_Texture*> tilesets;  // The tilesets used by the level.
  int MapWidth;                          // The width of the level map.
  int MapHeight;                         // The height of the level map.
  Sprite background;                     // The background sprite of the level.
};