// button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

#include "../display/display.hpp"
#include "../sprites/sprite.hpp"

class Bouton {
 public:
  /**
   * @brief Construct a new Bouton object
   */
  Bouton();
  /**
   * @brief Construct a new Bouton object
   *
   * @param Renderer
   * @param lien
   * @param x
   * @param y
   * @param w
   * @param h
   */
  Bouton(SDL_Renderer* Renderer, const char* lien, int x, int y, int w, int h);
  /**
   * @brief Destroy the Bouton object
   *
   */
  ~Bouton();

  /**
   * @brief Get the Rect object
   * @return SDL_Rect*
   */
  SDL_Rect* getRect();

  /**
   * @brief Get Width object
   * @return int
   */
  int getWidth();

  /**
   * @brief Get Height object
   * @return int
   */
  int getHeight();

  /**
   * @brief End the game
   */
  void gererFin(SDL_Event* evenement, SDL_Renderer* rendu, bool* quit);

  /**
   * @brief Start the game
   * @param evenement SDL_Event*
   * @param rendu SDL_Renderer*
   * @param var bool*
   */
  void gererPlay(SDL_Event* evenement, SDL_Renderer* rendu, bool* var);

  /**
   * @brief Get if the button is clicked
   * @param mouseX int
   * @param mouseY int
   * @return int
   */
  bool isColliding(int mouseX, int mouseY);

  /**
   * @brief Get the Y object
   * @return int
   */
  int getY();

  /**
   * @brief Get the X object
   * @return int
   */
  int getX();

  /**
   * @brief Draw the button on the screen
   * @param gRenderer SDL_Renderer*
   */
  void selfDraw(SDL_Renderer* gRenderer);

  /**
   * @brief Set the Surface object
   * @param x
   * @param y
   * @param w
   * @param h
   */
  void setSurface(int x, int y, int w, int h);

 private:
  Sprite image;
  SDL_Rect rect;
};

#endif  // BUTTON_HPP
