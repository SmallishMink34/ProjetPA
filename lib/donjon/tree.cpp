#include "tree.hpp"

#include <SDL2/SDL_ttf.h>

#include "../../Constante.hpp"

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

void rooms::setTall(int tall) { this->tall = tall; }

void rooms::setType(int type) { this->type = type; }

int rooms::getX() { return this->x; }

int rooms::getY() { return this->y; }

void rooms::setX(int x) { this->x = x; }

void rooms::setY(int y) { this->y = y; }

void rooms::drawRoom(SDL_Renderer *Renderer) {
  SDL_Rect rect;
  rect.x = 320 + this->x * 32;
  rect.y = 320 + this->y * 32;
  rect.w = 32;
  rect.h = 32;
  if(this->tall == 1) {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
  } else {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);
    rect.h *= 2;
  }

  SDL_RenderFillRect(Renderer, &rect);

  // Draw the value
  SDL_Color textColor = {0, 0, 0};
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, this->value.c_str(), textColor);
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);

  SDL_Rect textRect;
  textRect.x = rect.x + rect.w / 2 - textSurface->w / 2;
  textRect.y = rect.y + rect.h / 2 - textSurface->h / 2;
  textRect.w = textSurface->w;
  textRect.h = textSurface->h;
  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  SDL_RenderCopy(Renderer, textTexture, NULL, &textRect);
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
}

Node::Node(rooms *room, char value) {
  this->room = room;
  this->value = value;
  this->room->setValue(value);
}

std::vector<Node *> Node::getChildren() { return children; }

std::string Node::getAllChildValues() {
  std::string result;
  for(Node *child : getChildren()) {
    result += child->getValue();
  }
  return result;
}

char Node::getChildValue(int index) {
  if(index >= 0 && index < (int)children.size()) {
    return children[index]->value;
  }
  return '\0';  // Return null character instead of nullptr
}

void Node::addChild(Node *child) { this->children.push_back(child); }

int Node::length() { return this->children.size(); }

rooms *Node::getRoom() { return room; }

char Node::getValue() { return value; }

Node::~Node() { delete room; }