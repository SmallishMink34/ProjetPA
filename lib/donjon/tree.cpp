#include "tree.hpp"

#include <SDL2/SDL_ttf.h>

rooms::rooms() {
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
  this->type = 0;
  this->tall = 0;
  this->value = "0";
  this->font = TTF_OpenFont("src/font/Misty Style.otf", 24);
}

rooms::rooms(int x, int y) {
  this->x = x;
  this->y = y;
  this->w = 0;
  this->h = 0;
  this->type = 0;
  this->tall = 1;
  this->value = "0";
  this->font = TTF_OpenFont("src/font/Misty Style.otf", 24);
}

rooms::rooms(int x, int y, int w, int h, int type, int tall) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->type = type;
  this->tall = tall;
  this->value = '0';
  this->font = TTF_OpenFont("src/font/Misty Style.otf", 24);
}

void rooms::setTall(int tall) {
  this->tall = tall;
  if(this->tall == 1) {
    this->color = {0, 255, 255};
    this->defaultColor = {0, 255, 255};
  } else {
    this->color = {255, 0, 255};
    this->defaultColor = {255, 0, 255};
  }
}

void rooms::setType(int type) { this->type = type; }

void rooms::setColor(SDL_Color color) { this->color = color; }

void rooms::setColor(int r, int g, int b) {
  this->color.r = r;
  this->color.g = g;
  this->color.b = b;
}

int rooms::getX() { return this->x; }

int rooms::getY() { return this->y; }

void rooms::setX(int x) { this->x = x; }

void rooms::setY(int y) { this->y = y; }

SDL_Color rooms::getDefaultColor() { return this->defaultColor; }

void rooms::drawRoom(SDL_Renderer *Renderer) {
  SDL_Rect rect;
  rect.x = 320 + this->x * 32;
  rect.y = 320 + this->y * 32;
  rect.w = 32;
  rect.h = 32;
  if(this->tall == 1) {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, 255);
  } else {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, 255);
    rect.h *= 2;
  }

  SDL_RenderFillRect(Renderer, &rect);
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

rooms::~rooms() {  // TTF_CloseFont(font);
}

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