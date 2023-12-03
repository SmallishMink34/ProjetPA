#ifndef defTree
#define defTree
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <tuple>
#include <vector>
class rooms {
 private:
  int x;
  int y;
  int w;
  int h;
  int type;
  int tall;
  std::string value;
  TTF_Font *font;
  SDL_Color color;
  SDL_Color defaultColor;

 public:
  rooms();
  rooms(int x, int y);
  rooms(int x, int y, int w, int h, int type, int tall);

  // Setters :
  void setTall(int tall);
  void setType(int type);
  void setX(int x);
  void setY(int y);
  void setValue(char value);
  void setColor(SDL_Color color);
  void setColor(int r, int g, int b);

  // Getters :
  int getX();
  int getY();
  int getTall();
  int getType();
  SDL_Color getDefaultColor();

  // Others :
  void drawRoom(SDL_Renderer *Renderer);
  std::vector<std::pair<int, int>> coordsarround();

  ~rooms();
};

class Node {
 public:
  Node();
  Node(rooms *room, char value, std::string NodePlacement);

  // Getters :
  std::vector<std::pair<Node *, std::string>> getChildren();
  char getChildValue(int index);
  int length();
  rooms *getRoom();
  char getValue();
  std::string getAllChildValues();
  std::string getMap();
  std::vector<std::pair<Node *, std::string>> getChildAndParent();
  // Setters :
  void setMap(std::string Map);

  // Others :
  void addChild(Node *child, std::string NodePlacement);
  void addParent(Node *parent, std::string NodePlacement);

  ~Node();

 private:
  rooms *room;
  std::string Map;
  char value;
  std::vector<std::pair<Node *, std::string>> children;
  std::vector<std::pair<Node *, std::string>> childAndParent;
};
#endif