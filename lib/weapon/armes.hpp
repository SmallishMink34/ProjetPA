#ifndef ARMES_HPP
#define ARMES_HPP
#include <iostream>
#include <memory>
#include <vector>

#include "../maps/maps.hpp"
#include "../monster/monster.hpp"
#include "../sprites/sprite.hpp"

/**
 * @brief The balles class represents a bullet in the game.
 */
class balles {
 public:
  /**
   * @brief Constructs a new balles object.
   *
   * @param renderer The SDL renderer used for rendering.
   * @param x The initial x-coordinate of the bullet.
   * @param y The initial y-coordinate of the bullet.
   * @param dirrectionX The x-direction of the bullet.
   * @param dirrectionY The y-direction of the bullet.
   * @param degats The damage inflicted by the bullet.
   * @param portee The range of the bullet.
   */
  balles(SDL_Renderer* renderer, int x, int y, float dirrectionX, float dirrectionY, int degats, int portee);

  /**
   * @brief Destroys the balles object.
   */
  ~balles();

  /**
   * @brief Moves the bullet.
   */
  void move();

  /**
   * @brief Updates the bullet's position and checks for collisions with objects and monsters.
   *
   * @param collisions A vector of tmx::Object representing the collision objects in the game.
   * @param MonstreList A pointer to a vector of monster* representing the list of monsters in the game.
   * @return true if the bullet needs to be destroyed, false otherwise.
   */
  bool update(std::vector<tmx::Object> collisions, std::vector<monster*>* MonstreList);

  /**
   * @brief Draws the bullet on the screen.
   *
   * @param renderer The SDL renderer used for rendering.
   * @param dx The x-coordinate offset for rendering.
   * @param dy The y-coordinate offset for rendering.
   */
  void draw(SDL_Renderer* renderer, int dx, int dy);

  /**
   * @brief Checks if the bullet is colliding with a tmx::Object.
   *
   * @param object The tmx::Object to check collision with.
   * @return true if the bullet is colliding with the object, false otherwise.
   */
  bool isColliding(tmx::Object object);

  /**
   * @brief Checks if the bullet is colliding with a monster.
   *
   * @param monstre The monster to check collision with.
   * @return true if the bullet is colliding with the monster, false otherwise.
   */
  bool isColliding(monster* monstre);

 private:
  float vitesse;   // The speed of the bullet.
  float dirrX;     // The x-direction of the bullet.
  float dirrY;     // The y-direction of the bullet.
  int degats;      // The damage inflicted by the bullet.
  int portee;      // The range of the bullet.
  int counter;     // A counter used for tracking the bullet's lifespan.
  Sprite* sprite;  // The sprite representing the bullet.
  SDL_Rect rect;   // The rectangle representing the bullet's position and size.
};

/**
 * @brief The `armes` class represents a weapon.
 *
 * This class provides functionality to set collisions, fire bullets, draw the weapon, and update its state.
 */
class armes {
 public:
  /**
   * @brief Constructs an `armes` object.
   *
   * @param renderer The SDL renderer used for rendering.
   */
  armes(SDL_Renderer* renderer);

  /**
   * @brief Destroys the `armes` object.
   */
  ~armes();

  /**
   * @brief Sets the collisions and monster list for the weapon.
   *
   * @param collisions A vector of tmx::Object representing the collisions.
   * @param MonstreList A pointer to a vector of monster objects.
   */
  void setCollisions(std::vector<tmx::Object> collisions, std::vector<monster*>* MonstreList);

  /**
   * @brief Fires a bullet from the weapon.
   *
   * @param PlayerX The X coordinate of the player.
   * @param PlayerY The Y coordinate of the player.
   * @param PlayerRX The X coordinate of the player's hitbox.
   * @param PlayerRY The Y coordinate of the player's hitbox.
   * @param mouseX The X coordinate of the mouse.
   * @param mouseY The Y coordinate of the mouse.
   */
  void tir(int PlayerX, int PlayerY, int PlayerRX, int PlayerRY, int mouseX, int mouseY);

  /**
   * @brief Draws the weapon on the screen.
   *
   * @param renderer The SDL renderer used for rendering.
   * @param dx The X coordinate offset for drawing.
   * @param dy The Y coordinate offset for drawing.
   */
  void draw(SDL_Renderer* renderer, int dx, int dy);

  /**
   * @brief Updates the state of the weapon.
   */
  void update();

 private:
  int degats;                          /**< The damage of the weapon. */
  int portee;                          /**< The range of the weapon. */
  int cadence;                         /**< The firing rate of the weapon. */
  int counter;                         /**< The counter for controlling the firing rate. */
  std::vector<tmx::Object> collisions; /**< The collisions for the weapon. */
  std::vector<monster*>* MonstreList;  /**< A pointer to the monster list. */
  SDL_Renderer* renderer;              /**< The SDL renderer used for rendering. */
  std::vector<balles*> bullet;         /**< The bullets fired by the weapon. */
};

#endif