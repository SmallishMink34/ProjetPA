#include "donjon.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

#include "../utility/utility.hpp"
#include "tree.hpp"

donjon::donjon(int nbnoeuds, int seed = 1) : noeuds(nbnoeuds), max_noeuds(nbnoeuds), max_children(3), max_depth(10), seed(seed), specialRooms(3), remaining_count(nbnoeuds) {
  letter = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5',
            '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  dirrection = {"bas", "haut"};
  dirrectionCopy = dirrection;
  std::random_device rd;
  std::mt19937 g(rd());
  // std::shuffle(letter.begin(), letter.end(), g);
  // std::shuffle(dirrection.begin(), dirrection.end(), g);
  // std::shuffle(dirrectionCopy.begin(), dirrectionCopy.end(), g);
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
  for(Node *child : node->getChildren()) {
    Node *result = searchNode(x, y, child);
    if(result != nullptr) {
      return result;
    }
  }

  return nullptr;
}

Node *donjon::create_tree() {
  char root_value = addletter();
  Node *root = new Node(new rooms(0, 0, 32, 32, 2, 2), root_value);
  initial_Node = root;
  add_children(root, true, true, 0);
  return root;
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

void donjon::add_children(Node *node, bool CanBeTall, bool Continuer, int depth) {
  // Choix du nombre d'enfants
  int num_children;

  std::vector<bool> dirrectionUsed = {false, false};  // 0 = bas, 1 = haut

  node->getRoom()->setTall(2);

  // On regarde si la salle peut être placé en grande
  if(checkTallRoom(node->getRoom()->getX(), node->getRoom()->getY(), "bas")) {
    dirrectionUsed[0] = true;
  } else if(checkTallRoom(node->getRoom()->getX(), node->getRoom()->getY(), "haut")) {
    dirrectionUsed[1] = true;
    // node->getRoom()->setY(node->getRoom()->getY() - 1);
  } else {
    node->getRoom()->setTall(1);
  }

  // On met la salle en grande par défaut
  std::vector<std::pair<int, int>> valids = checks_valids(*node->getRoom());  // On regarde les salles autour de la salle actuelle
  int nombreEnfantsPossible = (int)valids.size();                             // On regarde le nombre de place disponible autour de la salle
  nombreEnfantsPossible = std::min(nombreEnfantsPossible, remaining_count);   // On prend le minimum entre le nombre de place disponible et le nombre de noeuds restant

  if(nombreEnfantsPossible <= 1) {
    CanBeTall = false;
  }

  if(!CanBeTall) {
    node->getRoom()->setTall(1);
    valids = checks_valids(*node->getRoom());
    nombreEnfantsPossible = (int)valids.size();
    nombreEnfantsPossible = std::min(nombreEnfantsPossible, remaining_count);
  }

  // Maintenant on choisis le nombre d'enfants en fonction du nombre de place disponible
  if(remaining_count == max_noeuds) {                                     // la racine
    num_children = std::min(nombreEnfantsPossible, std::rand() % 2 + 3);  // entre 3 et 4
  } else if(CanBeTall && node->getRoom()->getTall() == 2) {
    num_children = std::min(nombreEnfantsPossible, std::rand() % 3 + 1);  // entre 1 et 3
  } else {
    num_children = std::min(nombreEnfantsPossible, 1);
  }

  if(num_children == 1) {
    node->getRoom()->setTall(1);
  }

  if(node->getRoom()->getTall() == 2) {
    if(dirrectionUsed[1]) {
      node->getRoom()->setY(node->getRoom()->getY() - 1);
    }
    addCoords(std::make_pair(node->getRoom()->getX(), node->getRoom()->getY()));
    addCoords(std::make_pair(node->getRoom()->getX(), node->getRoom()->getY() + 1));
  } else {
    addCoords(std::make_pair(node->getRoom()->getX(), node->getRoom()->getY()));
  }

  if(depth >= max_depth) {
    num_children = 0;
  }

  remaining_count -= num_children;

  if(!Continuer) {
    return;
  }

  if(remaining_count <= 0) {
    Continuer = false;
  }

  for(int i = 0; i < num_children; i++) {
    valids = checks_valids(*node->getRoom());

    if(valids.empty()) {
      break;
    }
    char child_value = addletter();
    std::pair<int, int> coords = valids[std::rand() % valids.size()];
    std::remove(valids.begin(), valids.end(), coords);
    Node *child = new Node(new rooms(coords.first, coords.second), child_value);
    node->addChild(child);

    if(node->getRoom()->getTall() == 2) {
      CanBeTall = false;
    } else {
      CanBeTall = true;
    }
    add_children(child, CanBeTall, Continuer, depth + 1);
  }
}

void donjon::SearchCelibRooms(Node *node) {
  if(node != nullptr) {
    if(node->getChildren().empty() && node->getRoom()->getTall() == 1) {
      celibNode.push_back(node);
    } else {
      for(Node *i : node->getChildren()) {
        SearchCelibRooms(i);
      }
    }
  }
}

void donjon::addSpecialRooms(Node *node) {
  for(int i = 0; i < specialRooms; i++) {
    if(!celibNode.empty()) {
      node = celibNode[std::rand() % celibNode.size()];
      node->getRoom()->setType(2);
      celibNode.erase(std::remove(celibNode.begin(), celibNode.end(), node), celibNode.end());
    } else {
      break;
    }
  }
}

void donjon::save_rooms_to_file(Node *node) {
  std::ofstream file("map.txt");
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
    save_path_to_file(node);
  }
}

void donjon::parcours_iteratif_write(Node *node, std::ofstream &txt) {
  txt << node->getValue() << node->getRoom()->getTall() << node->getRoom()->getType();
  for(Node *i : node->getChildren()) {
    txt << i->getValue();
  }
  txt << "\n";
  for(Node *i2 : node->getChildren()) {
    parcours_iteratif_write(i2, txt);
  }
}

void donjon::save_path_to_file(Node *node) {
  std::ofstream file("mapPath.txt");
  parcours_iteratif_write(node, file);
  file.close();
}

int donjon::WidthLoad(std::ifstream &file) {
  int maxChar = 0;
  std::string line;
  while(std::getline(file, line)) {
    if(line.length() > maxChar) {
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
  std::ifstream file("map.txt");
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
  std::cout << "Letter " << letter << " not found in map " << std::endl;

  return std::make_pair(NULL, NULL);
}

void donjon::load_rooms_from_file() {
  std::ifstream file("map.txt");
  std::string line;

  std::pair<int, int> origin = SearchLetterInMapFromOrigin('A', 0, 0);

  initial_Node = new Node(new rooms(0, 0, 32, 32, 2, 2), 'A');

  addChildFromFile(initial_Node, origin.first, origin.second);
  file.close();
}

std::vector<char> donjon::getLetterAt(std::ifstream &file, int x, int y) {
  std::vector<char> letter;
  std::string line;
  int count = 0;
  while(std::getline(file, line)) {
    if(count == y - 1) {
      for(int i = 0; i < line.length(); i++) {
        if(i == x - 1) {
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

std::vector<char> donjon::getAdjacentLetterFromMap(char letter, int *tall) {
  std::vector<char> adjacentLetter;
  std::ifstream file("map.txt");
  std::vector<std::vector<char>> list = getListOfFile(file);
  std::pair<int, int> origin = SearchLetterInMapFromOrigin(letter, 0, 0);

  letterAlreadyUsed.push_back(letter);
  char a = getCharAt(list, origin.first, origin.second + 1);  // Bas
  std::vector<std::pair<int, int>> coords;
  if(a == letter) {
    *tall = 2;
    coords = {{1, 0}, {1, 1}, {-1, 1}, {-1, 0}};
  } else {
    coords = {{1, 0}, {-1, 0}};
    *tall = 1;
  }

  for(std::pair<int, int> coord : coords) {
    char a = getCharAt(list, origin.first + coord.first, origin.second + coord.second);
    if(a != '#' && findInVector(letterAlreadyUsed, a) == -1) adjacentLetter.push_back(a);
  }

  std::cout << "Letter : " << letter << " tall : " << *tall << std::endl;
  file.close();
  return adjacentLetter;
}

void donjon::addChildFromFile(Node *node, int originx, int originy) {
  if(node != nullptr) {
    int tall = 1;
    int type = 1;
    std::vector<char> letters = getAdjacentLetterFromMap(node->getValue(), &tall);
    node->getRoom()->setTall(tall);
    node->getRoom()->setType(type);
    for(char c : letters) {
      std::pair<int, int> NewNode = SearchLetterInMapFromOrigin(c, originx, originy);
      if(NewNode.first == NULL && NewNode.second == NULL) {
        continue;
      }

      Node *child = new Node(new rooms(NewNode.first, NewNode.second), c);
      node->addChild(child);
      addChildFromFile(child, originx, originy);
    }
  }
}
void donjon::drawDungeon(Node *node) {
  if(node != nullptr) {
    std::cout << node->getValue() << "\t" << node->getRoom()->getX() << "/" << node->getRoom()->getY() << "\t" << node->getAllChildValues()
              << "\ttall : " << node->getRoom()->getTall() << std::endl;
    for(Node *i : node->getChildren()) {
      drawDungeon(i);
    }
  }
}

void donjon::draw_tree(SDL_Renderer *Renderer, Node *node) {
  if(node != nullptr) {
    node->getRoom()->drawRoom(Renderer);
    for(Node *i : node->getChildren()) {
      draw_tree(Renderer, i);
    }
  }
}

void removeNode(Node *node) {
  if(node != nullptr) {
    for(Node *i : node->getChildren()) {
      removeNode(i);
    }
    delete node;
  }
}

donjon::~donjon() { removeNode(initial_Node); }