#include "tree.hpp"

#include <SDL2/SDL.h>

#include "../Variables/variables.hpp"

rooms::rooms() {
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
  this->type = 0;
  this->tall = 1;
  this->value = '0';
  this->loaded = false;
  setImages();
}

rooms::rooms(int x, int y) {
  this->x = x;
  this->y = y;
  this->w = 0;
  this->h = 0;
  this->type = 0;
  this->tall = 1;
  this->value = '0';
  this->loaded = false;
  setImages();
}

rooms::rooms(int x, int y, int w, int h, int type, int tall) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->type = type;
  this->tall = tall;
  this->value = '0';
  this->loaded = false;
  this->InRoom = false;
  setImages();
}

void rooms::setTall(int tall) {
  this->tall = tall;
  setImages();
}

void rooms::setType(int type) { this->type = type; }

void rooms::SetInTheRoom(bool in) { this->InRoom = in; }

int rooms::getX() { return this->x; }

int rooms::getY() { return this->y; }

void rooms::setX(int x) { this->x = x; }

void rooms::setY(int y) { this->y = y; }

void rooms::setImages() {
  if(this->tall == 1) {
    this->ImageIn = new Sprite("src/Images/HUD/Case1.png", 0, 0, this->w, this->h);
    this->ImageNotIn = new Sprite("src/Images/HUD/Case2.png", 0, 0, this->w, this->h);
  } else {
    this->ImageIn = new Sprite("src/Images/HUD/Case3.png", 0, 0, this->w, this->h * 2);
    this->ImageNotIn = new Sprite("src/Images/HUD/Case4.png", 0, 0, this->w, this->h * 2);
  }
}

void rooms::drawRoom(SDL_Renderer *Renderer, int x, int y) {
  if(!this->loaded) {
    this->ImageIn->loadImage(Renderer);
    this->ImageNotIn->loadImage(Renderer);
    this->loaded = true;
  }
  if(this->InRoom) {
    this->ImageIn->selfDraw(Renderer, x + this->x * tailleCase, y + this->y * tailleCase);
  } else {
    this->ImageNotIn->selfDraw(Renderer, x + this->x * tailleCase, y + this->y * tailleCase);
  }
}

std::vector<std::pair<int, int>> rooms::coordsarround() {
  std::vector<std::pair<int, int>> coords;
  if(getTall() == 2) {
    coords.push_back(std::pair<int, int>(getX() + 1, getY()));
    coords.push_back(std::pair<int, int>(getX() - 1, getY()));
    coords.push_back(std::pair<int, int>(getX() + 1, getY() + 1));
    coords.push_back(std::pair<int, int>(getX() - 1, getY() + 1));
  } else {
    coords.push_back(std::pair<int, int>(getX() + 1, getY()));
    coords.push_back(std::pair<int, int>(getX() - 1, getY()));
  }

  return coords;
}

int rooms::getTall() { return this->tall; }

int rooms::getType() { return this->type; }

void rooms::setValue(char value) { this->value = value; }

rooms::~rooms() {}

// |---------------------- NODE ----------------------|

Node::Node() {
  this->room = new rooms();
  this->value = '0';
  this->room->setValue('0');
  this->Map = "0";
}

Node::Node(rooms *room, char value, std::string NodePlacement) {
  this->room = room;
  this->value = value;
  this->room->setValue(value);
  this->Map = "0";
}

std::vector<std::pair<Node *, std::string>> Node::getChildren() { return children; }

std::vector<std::pair<Node *, std::string>> Node::getChildAndParent() { return childAndParent; }

std::string Node::getAllChildValues() {
  std::string result;
  for(std::pair<Node *, std::string> child : getChildren()) {
    result += child.first->getValue();
  }
  return result;
}

char Node::getChildValue(int index) {
  if(index >= 0 && index < (int)children.size()) {
    return children[index].first->value;
  }
  return '\0';  // Return null character instead of nullptr
}

void Node::addChild(Node *child, std::string NodePlacement) {
  children.push_back(std::pair<Node *, std::string>(child, NodePlacement));
  childAndParent.push_back(std::pair<Node *, std::string>(child, NodePlacement));
}

void Node::addParent(Node *parent, std::string NodePlacement) { childAndParent.push_back(std::pair<Node *, std::string>(parent, NodePlacement)); }

int Node::length() { return this->children.size(); }

rooms *Node::getRoom() { return room; }

char Node::getValue() { return value; }

void Node::setMap(std::string Map) { this->Map = Map; }
std::string Node::getMap() { return this->Map; }

Node::~Node() { delete room; }