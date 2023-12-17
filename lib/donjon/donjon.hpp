#ifndef DONJON_HPP
#define DONJON_HPP

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "tree.hpp"

/**
 * @class donjon
 * @brief Represents a donjon (dungeon) in a game.
 *
 * The donjon class is responsible for creating, saving, loading, and drawing the donjon.
 * It contains various methods for manipulating the donjon's structure and retrieving information about it.
 */
/**
 * @brief The donjon class represents a dungeon.
 */
class donjon {
 private:
  /**
   * @brief The number of nodes in the donjon.
   */
  int noeuds;
  int max_noeuds;
  int max_children;
  int max_depth;
  std::vector<char> letter;

  std::vector<std::string> dirrection;
  std::vector<std::string> dirrectionCopy;
  int seed;
  int specialRooms;

  int remaining_count;
  std::vector<Node*> celibNode;
  std::vector<char> letterAlreadyUsed;
  std::vector<std::string> TwoTallMaps;
  std::vector<std::string> OneTallMaps;
  SDL_Renderer* Renderer;

 public:
  /**
   * @brief Constructs a new donjon object.
   *
   * @param nbnoeuds The number of nodes in the donjon.
   * @param seed The seed for random number generation.
   */
  donjon(int nbnoeuds, SDL_Renderer* Renderer);

  std::vector<std::pair<int, int>> CoordUse;
  Node* initial_Node;

  /**
   * @brief get all the letters of the donjon
   */
  std::vector<char> getAllLetters(Node* node);

  /**
   * @brief get Random Node from the donjon
   * @param inital the initial node
   * @return a random node
   */
  Node* getRandomNode(Node* inital);

  /**
   * @brief Searches for a node with the given coordinates.
   *
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @param node The starting node for the search.
   * @return The found node, or nullptr if not found.
   */
  Node* searchNode(int x, int y, Node* node);

  /**
   * @brief Searches for a node with the given letter.
   *
   * @param c The letter to search for.
   * @param node The starting node for the search.
   * @return The found node, or nullptr if not found.
   */
  Node* searchNode(char c, Node* node);

  /**
   * @brief Adds coordinates to the CoordUse vector.
   *
   * @param coord The coordinates to add.
   * @return True if the coordinates were added successfully, false otherwise.
   */
  bool addCoords(std::pair<int, int> coord);

  /**
   * @brief Returns the minimum x-coordinate of the donjon.
   *
   * @return The minimum x-coordinate.
   */
  int minX();

  /**
   * @brief Returns the maximum x-coordinate of the donjon.
   *
   * @return The maximum x-coordinate.
   */
  int maxX();

  /**
   * @brief Returns the minimum y-coordinate of the donjon.
   *
   * @return The minimum y-coordinate.
   */
  int minY();

  /**
   * @brief Returns the maximum y-coordinate of the donjon.
   *
   * @return The maximum y-coordinate.
   */
  int maxY();

  //////////////////////////// Logique de création de donjon ////////////////////////////

  /**
   * @brief Checks for valid rooms adjacent to the given room.
   *
   * @param room The room to check.
   * @return A vector of valid adjacent coordinates.
   */
  std::vector<std::pair<int, int>> checks_valids(rooms room);

  ////////////// Sauvegarde du donjon ///////////////////////

  /**
   * @brief Saves the rooms of the donjon to a file.
   *
   * @param node The starting node for saving the rooms.
   */
  void save_rooms_to_file(Node* node);

  /**
   * @brief Writes the donjon tree to a file iteratively.
   *
   * @param node The starting node for writing the tree.
   * @param file The output file stream.
   */
  void parcours_iteratif_write(Node* node, std::ofstream& file);

  /**
   * @brief Loads the width of the donjon from a file.
   *
   * @param file The input file stream.
   * @return The loaded width.
   */
  int WidthLoad(std::ifstream& file);

  /**
   * @brief Loads the height of the donjon from a file.
   *
   * @param file The input file stream.
   * @return The loaded height.
   */
  int HeightLoad(std::ifstream& file);

  ////////////// Chargement du donjon ///////////////////////

  /**
   * @brief Searches for a letter in the donjon map starting from the origin coordinates.
   *
   * @param letter The letter to search for.
   * @param x The x-coordinate of the origin.
   * @param y The y-coordinate of the origin.
   * @return The coordinates of the found letter, or (-1, -1) if not found.
   */
  std::pair<int, int> SearchLetterInMapFromOrigin(char letter, int x, int y);

  /**
   * @brief Loads the rooms of the donjon from a file.
   * @return 0 if the rooms were loaded successfully, -1 otherwise.
   */
  int load_rooms_from_file();

  /**
   * @brief Gets the adjacent letters from the donjon map for a given letter.
   *
   * @param letter The letter to get adjacent letters for.
   * @param tall A pointer to store the number of tall rooms adjacent to the letter.
   * @return A vector of pairs, where each pair contains an adjacent letter and its direction.
   */
  std::vector<std::pair<char, std::string>> getAdjacentLetterFromMap(char letter, int* tall);

  /**
   * @brief Gets the adjacent type from one node to another.
   *
   * @param node1 The first node.
   * @param node2 The second node.
   * @return The type of adjacency between the nodes.
   */
  std::string getAdjacentTypeFromNode(Node* node1, Node* node2);

  /**
   * @brief Gets the letter at the specified coordinates in a file.
   *
   * @param file The input file stream.
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return The letter at the specified coordinates.
   */
  std::vector<char> getLetterAt(std::ifstream& file, int x, int y);

  /**
   * @brief Adds a child node to a node in the donjon tree from a file.
   *
   * @param node The parent node.
   * @param originx The x-coordinate of the parent node.
   * @param originy The y-coordinate of the parent node.
   * @param letter The letter of the child node.
   */
  void addChildFromFile(Node* node, int originx, int originy, char letter);

  /**
   * @brief Searches for a node with the specified value in the donjon tree.
   *
   * @param value The value to search for.
   * @param node The starting node for the search.
   * @return The found node, or nullptr if not found.
   */
  Node* SearchNodeFromValue(char value, Node* node);

  /**
   * @brief Gets the element in the child node based on the placement string.
   *
   * @param placement The placement string.
   * @param node The parent node.
   * @return The child node at the specified placement.
   */
  Node* getElementInChildFromPlacement(std::string placement, Node* node);

  // Getters

  /**
   * @brief Gets the actual room node from a node in the donjon tree.
   *
   * @param node The node to get the actual room node from.
   * @return The actual room node.
   */
  Node* getActualRoomNode(Node* node);

  ////////////// Dessin du donjon ///////////////////////

  /**
   * @brief Draws the donjon tree on the SDL renderer.
   *
   * @param Renderer The SDL renderer.
   * @param node The starting node for drawing the tree.
   * @param x The x-coordinate of the starting node.
   * @param y The y-coordinate of the starting node.
   * @param MapFrame The frame of the donjon map.
   */
  void draw_tree(SDL_Renderer* Renderer, Node* node, int x, int y, SDL_Rect MapFrame);

  /**
   * @brief Prints the coordinates in a vector of pairs.
   *
   * @param valid The vector of pairs to print.
   */
  void printPair(const std::vector<std::pair<int, int>>& valid);

  /**
   * @brief Draws the entire donjon on the screen.
   *
   * @param node The root node of the donjon tree.
   */
  void drawDungeon(Node* node);

  int getNbMonsterAllMap(Node* inital);

  bool allNodeVisited(Node* initial);

  void removeNode(Node* node);

  /**
   * @brief Destroys the donjon object and frees any allocated memory.
   */
  ~donjon();
};

#endif