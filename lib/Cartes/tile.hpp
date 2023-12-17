#include <SDL2/SDL.h>

#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"

/**
 * @brief Represents a tile in a game map.
 */
class Tile {
 private:
  Sprite* sprite; /**< Pointer to the sprite associated with the tile. */
  SDL_Rect* rect; /**< Pointer to the rectangle representing the tile's position and size. */
  std::string name;

 public:
  /**
   * @brief Constructs a Tile object with the given parameters.
   * @param Renderer The SDL renderer used for rendering the tile.
   * @param image The path to the image file used for the tile's sprite.
   * @param x The x-coordinate of the tile's position.
   * @param y The y-coordinate of the tile's position.
   * @param w The width of the tile.
   * @param h The height of the tile.
   */
  Tile(SDL_Renderer* Renderer, std::string image, int x, int y, int w, int h);

  /**
   * @brief Constructs a Tile object with the given parameters.
   * @param Renderer The SDL renderer used for rendering the tile.
   * @param image The path to the image file used for the tile's sprite.
   * @param x The x-coordinate of the tile's position.
   * @param y The y-coordinate of the tile's position.
   * @param w The width of the tile.
   * @param h The height of the tile.
   */
  Tile(SDL_Renderer* Renderer, std::string image, int x, int y, int w, int h, std::string name);

  /**
   * @brief Constructs a Tile object with the given parameters.
   * @param Renderer The SDL renderer used for rendering the tile.
   * @param t The tile object used for initializing the sprite and rectangle.
   * @param x The x-coordinate of the tile's position.
   * @param y The y-coordinate of the tile's position.
   * @param w The width of the tile.
   * @param h The height of the tile.
   */
  Tile(SDL_Renderer* Renderer, tile t, int x, int y, int w, int h);

  /**
   * @brief Destructor for the Tile object.
   */
  ~Tile();

  /**
   * @brief Gets the x-coordinate of the tile's position.
   * @return The x-coordinate of the tile's position.
   */
  int getX();

  /**
   * @brief Gets the y-coordinate of the tile's position.
   * @return The y-coordinate of the tile's position.
   */
  int getY();

  /**
   * @brief Gets the width of the tile.
   * @return The width of the tile.
   */
  int getWidth();

  /**
   * @brief Gets the height of the tile.
   * @return The height of the tile.
   */
  int getHeight();

  /**
   * @brief Gets the name of the tile.
   * @return The name of the tile.
   */
  std::string getName();

  /**
   * @brief Draws the tile on the given renderer at the specified position.
   * @param renderer The SDL renderer used for rendering the tile.
   * @param dx The x-coordinate of the destination position.
   * @param dy The y-coordinate of the destination position.
   */
  void draw(SDL_Renderer* renderer, int dx, int dy);
};
