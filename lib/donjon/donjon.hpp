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
  std::vector<std::pair<int, int>> CoordUse;
  std::vector<std::string> dirrection;
  std::vector<std::string> dirrectionCopy;
  int seed;
  int specialRooms;

  int remaining_count;
  std::vector<Node*> celibNode;

 public:
  donjon(int nbnoeuds, int seed);

  Node* initial_Node;
  char addletter();
  Node* searchNode(int x, int y, Node* node);
  Node* create_tree();
  bool addCoords(std::pair<int, int> coord);
  int minX();
  int maxX();
  int minY();
  int maxY();
  std::vector<std::pair<int, int>> checks_valids(rooms room);
  bool checkTallRoom(int x, int y, std::string dirr = "bas");
  void add_children(Node* node, bool CanBeTall, bool Continuer, int depth);
  void SearchCelibRooms(Node* node);
  void addSpecialRooms(Node* node);
  void save_rooms_to_file(Node* node);
  void parcours_iteratif_write(Node* node, std::ofstream& file);
  void save_path_to_file(Node* node);
  int WidthLoad(std::ifstream& file);
  int HeightLoad(std::ifstream& file);
  std::pair<int, int> SearchFromOrigin(char letter, int x, int y);
  void load_rooms_from_file();
  // void drawDungeon()
  void draw_tree(Node* node, int x, int y, int level);
  void drawDungeon(Node* node);
  std::vector<char> donjongetChildFromFile(std::ifstream& file, char letter);
  void addChildFromFile(Node* node, std::ifstream& file, std::ifstream& file2, std::pair<int, int> origin);
  void draw_tree(SDL_Renderer* Renderer, Node* node);
  void printPair(const std::vector<std::pair<int, int>>& valid);

  ~donjon();
};

#endif