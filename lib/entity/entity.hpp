#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include <SDL2/SDL_mixer.h>
#include "../Variables/variables.hpp"
#include "../entity/entity.hpp"
#include "../maps/maps.hpp"
#include "../sprites/sprite.hpp"
#include "../utility/utility.hpp"

/**
 * @brief The Entity class represents a generic entity in the game.
 *
 * This class provides methods to get and set various properties of an entity,
 * such as its position, size, velocity, and health. It also includes methods
 * for movement, collision detection, and updating the entity's state.
 */
/**
 * @brief The Entity class represents a game entity.
 *
 * This class provides various methods and attributes to manage the behavior and properties of a game entity.
 */
class Entity {
 public:
  /**
   * @brief Default constructor for the Entity class.
   */
  Entity();

  /**
   * @brief Virtual destructor for the Entity class.
   */
  virtual ~Entity();

  /**
   * @brief Get the current life points of the entity.
   * @return The current life points of the entity.
   */
  virtual int getVie();

  /**
   * @brief Get the x-coordinate of the entity on the screen.
   * @return The x-coordinate of the entity.
   */
  virtual int getX();

  /**
   * @brief Get the y-coordinate of the entity on the screen.
   * @return The y-coordinate of the entity.
   */
  virtual int getY();

  /**
   * @brief Get the real x-coordinate of the entity.
   * @return The real x-coordinate of the entity.
   */
  virtual int getRX();

  /**
   * @brief Get the real y-coordinate of the entity.
   * @return The real y-coordinate of the entity.
   */
  virtual int getRY();

  /**
   * @brief Get the width of the entity.
   * @return The width of the entity.
   */
  virtual int getWidth();

  /**
   * @brief Get the height of the entity.
   * @return The height of the entity.
   */
  virtual int getHeight();

  /**
   * @brief Get the center x-coordinate of the entity.
   * @return The center x-coordinate of the entity.
   */
  virtual int getCRX();

  /**
   * @brief Get the center y-coordinate of the entity.
   * @return The center y-coordinate of the entity.
   */
  virtual int getCRY();

  /**
   * @brief Get the center x-coordinate of the entity on the screen.
   * @return The center x-coordinate of the entityon the screen.
   */
  virtual int getCX();

  /**
   * @brief Get the center y-coordinate of the entity on the screen.
   * @return The center y-coordinate of the entity on the screen.
   */
  virtual int getCY();

  /**
   * @brief Set the x-coordinate of the entity.
   * @param x The new x-coordinate of the entity.
   */
  virtual void setX(int x);

  /**
   * @brief Set the y-coordinate of the entity.
   * @param y The new y-coordinate of the entity.
   */
  virtual void setY(int y);

  /**
   * @brief Set the jumping state of the entity.
   * @param Jump The new jumping state of the entity.
   */
  void setIsJumping(bool Jump);

  /**
   * @brief Set the vertical velocity of the entity.
   * @param velocity The new vertical velocity of the entity.
   */
  void setVerticalVelocity(float velocity);

  /**
   * @brief Increment the life points of the entity.
   * @param vie The amount to increment the life points by.
   */
  virtual void IncrementVie(int vie);

  /**
   * @brief Move the entity to a specific position.
   */
  virtual void Moveto();

  /**
   * @brief Move the entity to a specific position.
   * @param x The x-coordinate of the new position.
   * @param y The y-coordinate of the new position.
   */
  virtual void RealMoveto(int x, int y);

  /**
   * @brief Move the entity by a specified amount.
   * @param x The amount to move the entity in the x-direction.
   * @param y The amount to move the entity in the y-direction.
   * @param dxMap The change in the x-coordinate of the map.
   * @param dyMap The change in the y-coordinate of the map.
   */
  virtual void Move(int x, int y, int dxMap, int dyMap);

  /**
   * @brief Move the entity to a specific position and update the map coordinates.
   * @param x1 The x-coordinate of the new position.
   * @param y1 The y-coordinate of the new position.
   * @param Teleport Flag indicating if the movement is a teleportation.
   */
  virtual void AllMove(int x1, int y1, bool Teleport);

  /**
   * @brief Make the entity jump.
   */
  virtual void jump();

  /**
   * @brief Apply knockback to the entity.
   * @param monstre The entity causing the knockback.
   */
  virtual void knockback(Entity* monstre);

  /**
   * @brief Get the vertical velocity of the entity.
   * @return The vertical velocity of the entity.
   */
  virtual float getVerticalVelocity();

  /**
   * @brief Check if the entity is currently jumping.
   * @return True if the entity is jumping, false otherwise.
   */
  virtual bool isJumping();

  /**
   * @brief Check if the entity is on the ground.
   * @return True if the entity is on the ground, false otherwise.
   */
  virtual bool isOnGround();

  /**
   * @brief Apply gravity to the entity.
   */
  virtual void applyGravity();

  /**
   * @brief Check if the entity is colliding with a rectangle.
   * @param x The x-coordinate of the rectangle.
   * @param y The y-coordinate of the rectangle.
   * @param w The width of the rectangle.
   * @param h The height of the rectangle.
   * @return True if the entity is colliding with the rectangle, false otherwise.
   */
  virtual bool isColliding(int x, int y, int w, int h);

  /**
   * @brief Check if the entity is colliding with objects in a specific position.
   * @param realx The x-coordinate of the position.
   * @param realy The y-coordinate of the position.
   * @return A vector of pairs, where each pair contains an object and a string representing the collision type.
   */
  virtual std::vector<std::pair<tmx::Object, std::string>> isColliding(int realx, int realy);

  /**
   * @brief Check if the entity is colliding with objects in a specific position.
   * @param Collisions A vector of objects to check for collision.
   * @return The object with which the entity is colliding, or nullptr if there is no collision.
   */
  virtual tmx::Object isColliding(std::vector<tmx::Object> Collisions);

  /**
   * @brief Check if the entity is colliding with another entity.
   * @param entity The entity to check for collision.
   * @return True if the entity is colliding with the other entity, false otherwise.
   */
  virtual bool isCollidingEntity(Entity* entity);

  std::vector<tmx::Object> Collisions;  // List of collision objects

  /**
   * @brief Update the entity's state based on the current time.
   * @param currentTime The current time in milliseconds.
   */
  virtual void update(Uint32 currentTime);

  /**
   * @brief Inflict damage to the entity.
   * @param damage The amount of damage to inflict.
   * @return True if the entity takes damage, false otherwise.
   */
  virtual bool takeDamage(int damage);

  int vie;      // Life points
  int speed;    // Movement speed
  int x;        // x-coordinate
  int y;        // y-coordinate
  int width;    // Width
  int height;   // Height
  int Rwidth;   // Real width on the image
  int Rheight;  // Real height on the image
  int Realx;    // Real x-coordinate
  int Realy;    // Real y-coordinate
  int deltax;   // Change in x-coordinate
  int deltay;   // Change in y-coordinate

  int mapDX;     // Change in x-coordinate of the map
  int mapDY;     // Change in y-coordinate of the map
  Sprite Image;  // Entity's sprite

  std::map<std::string, std::vector<std::pair<int, int>>> etats;  // Map of entity's states
  std::string etat;                                               // Current entity state

  /**
   * @brief Animate the entity.
   * @param i The index of the animation frame.
   */
  void AnimEntity(int i);

  Uint32 previousDamageTime;  // Time of the previous damage

  bool OnGround;              // Flag indicating if the entity is on the ground
  bool Jumping;               // Flag indicating if the entity is jumping
  bool hasJump;               // Flag indicating if the entity has jumped
  bool canTakeDamage;         // Flag indicating if the entity can take damage
  bool istakeDamage;          // Flag indicating if the entity is taking damage
  float verticalVelocity;     // Vertical velocity
  float jumpStrength;         // Jump strength
  float jumpTime;             // Jump time
  float dy;                   // Change in y-coordinate
  long unsigned int Animcpt;  // Animation Counter
};

#endif