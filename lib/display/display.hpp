#ifndef DefDisplay
#define DefDisplay

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "../sprites/sprite.hpp"

/**
 * @brief The Texture class represents a texture that can be rendered on the screen.
 */
class Texture {
 public:
  /**
   * @brief Constructs a new Texture object.
   */
  Texture();

  /**
   * @brief A vector of Sprite objects representing the elements to be rendered.
   */
  std::vector<Sprite> Elements;

  /**
   * @brief Adds a Sprite element to the texture.
   *
   * @param Renderer The SDL renderer used for rendering.
   * @param Element The Sprite element to be added.
   */
  void addElements(SDL_Renderer* Renderer, Sprite Element);

  /**
   * @brief Draws all the elements of the texture on the screen.
   *
   * @param renderer The SDL renderer used for rendering.
   */
  void drawElements(SDL_Renderer* renderer);
};

/**
 * @brief Loads a texture from an image file.
 *
 * @param Renderer The SDL renderer used for rendering.
 * @param path The path to the image file.
 * @return SDL_Texture* The loaded texture.
 */
SDL_Texture* loadTexture(SDL_Renderer* Renderer, const std::string& path);

#endif