#include "donjon.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

#include "../Variables/variables.hpp"
#include "../utility/utility.hpp"
#include "tree.hpp"

donjon::donjon(int nbnoeuds, SDL_Renderer *Renderer) : noeuds(nbnoeuds), max_noeuds(nbnoeuds), max_children(3), max_depth(10), specialRooms(3), remaining_count(nbnoeuds) {
  this->seed = getSeedFromFile("map.txt");
  std::random_device rd;
  std::mt19937 g(this->seed);

  for(int i = 1; i <= nbTwoTallMaps; i++) {
    TwoTallMaps.push_back(std::to_string(i));
  }

  for(int i = 1; i <= nbOneTallMaps; i++) {
    OneTallMaps.push_back(std::to_string(i));
  }

  initial_Node = nullptr;
  this->Renderer = Renderer;
}

std::vector<char> donjon::getAllLetters(Node *node) {
  std::vector<char> letters;
  if(node != nullptr) {
    letters.push_back(node->getValue());
    for(std::pair<Node *, std::string> i : node->getChildren()) {
      std::vector<char> result = getAllLetters(i.first);
      letters.insert(letters.end(), result.begin(), result.end());
    }
  }
  return letters;
}

Node *donjon::searchNode(char c, Node *node) {
  if(node->getValue() == c) {
    return node;
  }
  for(std::pair<Node *, std::string> child : node->getChildren()) {
    Node *result = searchNode(c, child.first);
    if(result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

Node *donjon::getRandomNode(Node *inital) {
  if(inital != nullptr) {
    std::vector<char> letters = getAllLetters(inital);
    if(letters.size() > 0) {
      std::random_device rd;
      std::mt19937 g(seed);
      std::shuffle(letters.begin(), letters.end(), g);
      char c = letters[0];
      return searchNode(c, inital);
    }
  }
  return nullptr;
}

Node *donjon::searchNode(int x, int y, Node *node) {
  if(node->getRoom()->getX() == x && (node->getRoom()->getY() == y || (node->getRoom()->getY() == y - 1 && node->getRoom()->getTall() == 2))) {
    return node;
  }
  for(std::pair<Node *, std::string> child : node->getChildren()) {
    Node *result = searchNode(x, y, child.first);
    if(result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

Node *getRandomRoom(Node *inital) { return nullptr; }

bool donjon::addCoords(std::pair<int, int> coords) {
  if(std::find(CoordUse.begin(), CoordUse.end(), coords) == CoordUse.end()) {
    CoordUse.push_back(coords);
    return true;
  }
  return false;
}

int donjon::minX() {
  return std::min_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) { return a.first < b.first; })->first;
}

int donjon::maxX() {
  return std::max_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) { return a.first < b.first; })->first;
}

int donjon::minY() {
  return std::min_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) { return a.second < b.second; })->second;
}

int donjon::maxY() {
  return std::max_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) { return a.second < b.second; })->second;
}

void donjon::printPair(const std::vector<std::pair<int, int>> &valid) {
  for(const auto &coord : valid) {
    std::cout << "(" << coord.first << ", " << coord.second << ")";
  }
  std::cout << std::endl;
}

std::vector<std::pair<int, int>> donjon::checks_valids(rooms room) {
  std::vector<std::pair<int, int>> valid = room.coordsarround();
  for(const std::pair<int, int> &i : room.coordsarround()) {
    if(std::find(CoordUse.begin(), CoordUse.end(), i) != CoordUse.end()) {
      valid.erase(std::remove(valid.begin(), valid.end(), i), valid.end());
    }
  }
  return valid;
}

void donjon::save_rooms_to_file(Node *node) {
  std::ofstream file(MAP);
  if(file.is_open()) {
    for(int y = minY() - 1; y <= maxY() + 1; y++) {
      for(int x = minX() - 1; x <= maxX() + 1; x++) {
        if(std::find(CoordUse.begin(), CoordUse.end(), std::make_pair(x, y)) != CoordUse.end()) {
          Node *searchnode = searchNode(x, y, node);
          file << searchnode->getValue();
        } else {
          file << "#";
        }
      }
      file << "\n";
    }
    file.close();
  }
}

void donjon::parcours_iteratif_write(Node *node, std::ofstream &txt) {
  txt << node->getValue() << node->getRoom()->getTall() << node->getRoom()->getType();
  for(std::pair<Node *, std::string> i : node->getChildren()) {
    txt << i.first->getValue();
  }
  txt << "\n";
  for(std::pair<Node *, std::string> i2 : node->getChildren()) {
    parcours_iteratif_write(i2.first, txt);
  }
}

int donjon::WidthLoad(std::ifstream &file) {
  int maxChar = 0;
  std::string line;
  while(std::getline(file, line)) {
    if(line.length() > (long unsigned int)maxChar) {
      maxChar = line.length();
    }
  }
  file.clear();
  file.seekg(0, std::ios::beg);
  return maxChar;
}

int donjon::HeightLoad(std::ifstream &file) {
  int count = 0;
  std::string line;
  while(std::getline(file, line)) {
    count++;
  }
  file.clear();
  file.seekg(0, std::ios::beg);
  return count;
}

std::pair<int, int> donjon::SearchLetterInMapFromOrigin(char letter, int x, int y) {
  int oldx = 0;
  int oldy = 0;
  std::ifstream file(MAP);
  std::string line;

  while(std::getline(file, line)) {
    if(line.length() != 0 && line[0] != '#') {
      for(char c : line) {
        if(c == letter) {
          file.close();
          return std::make_pair(oldx - x, oldy - y);
        }
        oldx++;
      }
      oldy++;
      oldx = 0;
    }
  }
  file.close();
  std::cerr << "Letter " << letter << " not found in map " << std::endl;

  return std::make_pair(-5000, -5000);
}

int donjon::load_rooms_from_file() {
  std::ifstream file(MAP);
  std::string line;

  std::pair<int, int> origin = SearchLetterInMapFromOrigin('A', 0, 0);
  if(origin.first == -5000 || origin.second == -5000) {
    return -1;
  }

  initial_Node = new Node(new rooms(Renderer, 0, 0, tailleCase, tailleCase, 2, 2), 'A', "None");
  initial_Node->setMap("1");

  addChildFromFile(initial_Node, origin.first, origin.second, 'A');

  getRandomNode(initial_Node)->getRoom()->setIsEnd(true);

  file.close();
  return 0;
}

std::vector<char> donjon::getLetterAt(std::ifstream &file, int x, int y) {
  std::vector<char> letter;
  std::string line;
  int count = 0;
  while(std::getline(file, line)) {
    if(count == y - 1) {
      for(long unsigned int i = 0; i < line.length(); i++) {
        if(i == (long unsigned int)x - 1) {
          letter.push_back(line[i]);
        }
      }
      break;
    }
    count++;
  }
  file.clear();
  file.seekg(0, std::ios::beg);
  return letter;
}

std::vector<std::pair<char, std::string>> donjon::getAdjacentLetterFromMap(char letter, int *tall) {
  std::vector<std::pair<char, std::string>> adjacentLetter;
  std::ifstream file(MAP);
  std::vector<std::vector<char>> list = getListOfFile(file);
  std::pair<int, int> origin = SearchLetterInMapFromOrigin(letter, 0, 0);

  letterAlreadyUsed.push_back(letter);
  char a = getCharAt(list, origin.first, origin.second + 1);  // Bas
  std::vector<std::tuple<int, int, std::string>> coords;
  if(a == letter) {
    *tall = 2;
    coords = {{1, 0, "TR"}, {1, 1, "DR"}, {-1, 1, "DL"}, {-1, 0, "TL"}};
  } else {
    coords = {{1, 0, "TR"}, {-1, 0, "TL"}};
    *tall = 1;
  }

  for(std::tuple<int, int, std::string> coord : coords) {
    char a = getCharAt(list, origin.first + std::get<0>(coord), origin.second + std::get<1>(coord));
    std::cout << "char : " << a << std::endl;
    if(std::find(charMap.begin(), charMap.end(), a) != charMap.end()) adjacentLetter.push_back({a, std::get<2>(coord)});
  }

  file.close();
  return adjacentLetter;
}

void donjon::addChildFromFile(Node *node, int originx, int originy, char letter) {
  if(node != nullptr) {
    int tall = 1;
    int type = 1;
    std::vector<std::pair<char, std::string>> letters = getAdjacentLetterFromMap(node->getValue(), &tall);
    node->getRoom()->setTall(tall);
    node->getRoom()->setType(type);
    seed++;
    std::mt19937 g(seed);
    if(tall == 2) {
      node->setMap(getRandomElement(TwoTallMaps));
    } else {
      node->setMap(getRandomElement(OneTallMaps));
    }

    for(std::pair<char, std::string> c : letters) {
      if(findInVector(letterAlreadyUsed, c.first) == -1) {
        std::pair<int, int> NewNode = SearchLetterInMapFromOrigin(c.first, originx, originy);
        Node *child = new Node(new rooms(Renderer, NewNode.first, NewNode.second, tailleCase, tailleCase, 1, 1), c.first, c.second);
        node->addChild(child, c.second);
        addChildFromFile(child, originx, originy, node->getValue());
      } else if(c.first == letter) {
        Node *child = SearchNodeFromValue(c.first, initial_Node);
        node->addParent(child, c.second);
      }
    }
  }
}

void donjon::drawDungeon(Node *node) {
  if(node != nullptr) {
    std::cout << node->getValue() << "\t" << node->getRoom()->getX() << "/" << node->getRoom()->getY() << "\t" << node->getAllChildValues()
              << "\ttall : " << node->getRoom()->getTall() << std::endl;
    for(std::pair<Node *, std::string> i : node->getChildren()) {
      drawDungeon(i.first);
    }
  }
}

void donjon::draw_tree(SDL_Renderer *Renderer, Node *node, int x, int y, SDL_Rect MapFrame) {
  if(node != nullptr) {
    node->getRoom()->drawRoom(Renderer, x, y, MapFrame);
    for(std::pair<Node *, std::string> i : node->getChildren()) {
      draw_tree(Renderer, i.first, x, y, MapFrame);
    }
  }
}

Node *donjon::getElementInChildFromPlacement(std::string placement, Node *node) {
  if(node != nullptr) {
    for(std::pair<Node *, std::string> i : node->getChildAndParent()) {
      if(i.second == placement) {
        return i.first;
      }
    }
  }
  return nullptr;
}

Node *donjon::SearchNodeFromValue(char value, Node *node) {
  if(node->getValue() == value) {
    return node;
  }
  for(std::pair<Node *, std::string> child : node->getChildren()) {
    Node *result = SearchNodeFromValue(value, child.first);
    if(result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

std::string donjon::getAdjacentTypeFromNode(Node *node1, Node *node2) {
  std::vector<std::pair<char, std::string>> adjacentLetter;
  std::ifstream file(MAP);
  std::vector<std::vector<char>> list = getListOfFile(file);
  std::pair<int, int> origin = SearchLetterInMapFromOrigin(node1->getValue(), 0, 0);

  char a = getCharAt(list, origin.first, origin.second + 1);  // Bas
  std::vector<std::tuple<int, int, std::string>> coords;
  if(a == node1->getValue()) {
    coords = {{1, 0, "TR"}, {1, 1, "DR"}, {-1, 1, "DL"}, {-1, 0, "TL"}};
  } else {
    coords = {{1, 0, "TR"}, {-1, 0, "TL"}};
  }

  for(std::tuple<int, int, std::string> coord : coords) {
    if(getCharAt(list, origin.first + std::get<0>(coord), origin.second + std::get<1>(coord)) == node2->getValue()) {
      return std::get<2>(coord);
    }
  }

  return "None";
}

Node *donjon::getActualRoomNode(Node *node) {
  if(node != nullptr) {
    if(node->getRoom()->getInRoom()) {
      return node;
    } else {
      for(std::pair<Node *, std::string> i : node->getChildren()) {
        Node *result = getActualRoomNode(i.first);
        if(result != nullptr) {
          return result;
        }
      }
    }
  }
  return nullptr;
}

int donjon::getNbMonsterAllMap(Node *initial) {
  int nbMonster = 0;
  if(initial != nullptr) {
    nbMonster += initial->getRoom()->getNbMonster();

    for(std::pair<Node *, std::string> i : initial->getChildren()) {
      nbMonster += getNbMonsterAllMap(i.first);
    }
  }
  return nbMonster;
}

bool donjon::allNodeVisited(Node *initial) {
  bool visited = true;
  if(initial != nullptr) {
    if(!initial->getRoom()->getVisited()) {
      return false;
    }
    for(std::pair<Node *, std::string> i : initial->getChildren()) {
      visited = visited && allNodeVisited(i.first);
    }
  }
  return visited;
}

void donjon::removeNode(Node *node) {
  if(node != nullptr) {
    for(std::pair<Node *, std::string> i : node->getChildren()) {
      removeNode(i.first);
    }
    std::cout << "Suppression de " << node->getValue() << std::endl;
    if(node != nullptr) delete node;
    std::cout << "Suppression de terminé" << std::endl;
  }
}
donjon::~donjon() { removeNode(initial_Node); }
