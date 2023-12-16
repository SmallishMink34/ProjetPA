#include "donjon.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

#include "../Variables/variables.hpp"
#include "../utility/utility.hpp"
#include "tree.hpp"

donjon::donjon(int nbnoeuds, int seed = 1) : noeuds(nbnoeuds), max_noeuds(nbnoeuds), max_children(3), max_depth(10), seed(seed), specialRooms(3), remaining_count(nbnoeuds) {
  letter = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5',
            '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  dirrection = {"bas", "haut"};
  dirrectionCopy = dirrection;
  std::random_device rd;
  std::mt19937 g(getSeedFromFile("map.txt"));

  for(int i = 1; i <= nbTwoTallMaps; i++) {
    TwoTallMaps.push_back(std::to_string(i));
  }

  for(int i = 1; i <= nbOneTallMaps; i++) {
    OneTallMaps.push_back(std::to_string(i));
  }

  initial_Node = nullptr;
}

char donjon::addletter() {
  char a = letter[0];
  letter.erase(letter.begin());
  return a;
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

bool donjon::checkTallRoom(int x, int y, std::string dirr) {
  return (std::find(CoordUse.begin(), CoordUse.end(), std::make_pair(x, y + (dirr == "bas" ? 1 : -1))) == CoordUse.end());
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
    for(char c : line) {
      if(c == letter) {
        return std::make_pair(oldx - x, oldy - y);
      }
      oldx++;
    }
    oldy++;
    oldx = 0;
  }
  file.close();
  std::cerr << "Letter " << letter << " not found in map " << std::endl;

  return std::make_pair(NULL, NULL);
}

void donjon::load_rooms_from_file() {
  std::ifstream file(MAP);
  std::string line;

  std::pair<int, int> origin = SearchLetterInMapFromOrigin('A', 0, 0);

  initial_Node = new Node(new rooms(0, 0, tailleCase, tailleCase, 2, 2), 'A', "None");
  initial_Node->setMap("1");

  addChildFromFile(initial_Node, origin.first, origin.second, 'A');
  file.close();
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
    if(a != '#') adjacentLetter.push_back({a, std::get<2>(coord)});
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
        Node *child = new Node(new rooms(NewNode.first, NewNode.second, tailleCase, tailleCase, 1, 1), c.first, c.second);
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
      std::cout << "Suppression de " << i.first->getValue() << std::endl;
      removeNode(i.first);
    }
    delete node;
  }
}
donjon::~donjon() { removeNode(initial_Node); }
