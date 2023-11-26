#pragma once

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

class level {
 public:
  level(const std::string& name);
  void load(const std::string& path, SDL_Renderer* ren);
  void draw(SDL_Renderer* ren, int dx, int dy);
  tmx::Object getObjectByName(const std::string& Name);
  std::vector<tmx::Object> getObjectsByType(const std::string& Name);
  int getMapWidth();
  int getMapHeight();

 private:
  std::string name;
  std::string tmxFilePath;
  // Think of the dimensions as a 2D array (after all, that's what our
  // Tiled map is)
  // The rows variable is the number of tiles from top to bottom (Y axis).
  int rows;
  // The cols variable is the number of tiles from left to right (X axis).
  int cols;
  int tile_width;
  int tile_height;
  // All of the tiles we will draw to the screen.
  std::vector<tile> tiles;  // Like library in python
  // All of the tilesets used by our Tiled map.
  std::map<gid, SDL_Texture*> tilesets;
  int MapWidth;
  int MapHeight;
  Sprite background;
};
