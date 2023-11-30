#ifndef DONJON_HPP
#define DONJON_HPP

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "tree.hpp"

class donjon {
 private:
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

 public:
  donjon(int nbnoeuds, int seed);
  std::vector<std::pair<int, int>> CoordUse;
  Node* initial_Node;
  char addletter();
  Node* searchNode(int x, int y, Node* node);
  Node* create_tree();
  bool addCoords(std::pair<int, int> coord);
  int minX();
  int maxX();
  int minY();
  int maxY();

  //////////////////////////// Logique de création de donjon ////////////////////////////
  std::vector<std::pair<int, int>> checks_valids(rooms room);
  bool checkTallRoom(int x, int y, std::string dirr = "bas");
  void add_children(Node* node, bool CanBeTall, bool Continuer, int depth);
  void SearchCelibRooms(Node* node);
  void addSpecialRooms(Node* node);
  ////////////// Sauvegarde du donjon ///////////////////////
  void save_rooms_to_file(Node* node);
  void parcours_iteratif_write(Node* node, std::ofstream& file);
  void save_path_to_file(Node* node);
  int WidthLoad(std::ifstream& file);
  int HeightLoad(std::ifstream& file);

  ////////////// Chargement du donjon ///////////////////////
  std::pair<int, int> SearchLetterInMapFromOrigin(char letter, int x, int y);
  void load_rooms_from_file();
  std::vector<char> getAdjacentLetterFromMap(char letter);
  std::vector<char> getChildFromMapPath(char letter);

  /**
   * @brief Get the Tall Type From Map Path object
   * @param letter Search the letter in the paht
   * @param wyw 1 = Tall, 2 = Type
   */
  char getTallTypeFromMapPath(char letter, int wyw);
  void addChildFromFile(Node* node);

  ////////////// Dessin du donjon ///////////////////////
  void draw_tree(SDL_Renderer* Renderer, Node* node);
  void printPair(const std::vector<std::pair<int, int>>& valid);
  void drawDungeon(Node* node);
  ~donjon();
};

#endif