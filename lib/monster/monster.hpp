#ifndef Monster_HPP
#define Monster_HPP

#include <iostream>

#include "../entity/entity.hpp"

/**
 * @class monster
 * @brief Represents a monster entity in the game.
 *
 * This class inherits from the Entity class and provides additional functionality specific to monsters.
 */
class monster: public Entity {
 public:
  /**
   * @brief Constructs a monster object.
   * @param Renderer The SDL renderer used for rendering.
   */
  monster(SDL_Renderer* Renderer);

  // Variables

  // Fonctions
  /**
   * @brief Initializes the monster with collision objects.
   * @param Collisions A vector of collision objects.
   */
  void InitMonster(std::vector<tmx::Object> Collisions);

  /**
   * @brief Performs AI calculations for the monster.
   * @param dx The change in x-coordinate.
   * @param dy The change in y-coordinate.
   */
  void ai(int dx, int dy);

  /**
   * @brief Moves the monster to a new position on the map.
   * @param x1 The new x-coordinate.
   * @param y1 The new y-coordinate.
   * @param dxMap The change in x-coordinate on the map.
   * @param dyMap The change in y-coordinate on the map.
   */
  void Move(int x1, int y1, int dxMap, int dyMap) override;

 private:
  // Variables
  std::string aiDirrection;  ///< The direction of the monster's AI.
  std::string Nom;           ///< The name of the monster.
  
};

#endif