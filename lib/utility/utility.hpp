#ifndef defutility
#define defutility
#include <fstream>
#include <iostream>
#include <vector>

#include "../donjon/donjon.hpp"
#include "tmxlite/Map.hpp"

int findInVector(std::vector<char> vec, char value);
std::vector<std::vector<char>> getListOfFile(std::ifstream &file);

int width(std::vector<std::vector<char>> list);
int height(std::vector<std::vector<char>> list);

char getCharAt(std::vector<std::vector<char>> list, int x, int y);

std::string getRandomElement(std::vector<std::string> vec);

int getNumverInList(std::vector<char> vec);

tmx::Property getPropertyFromName(std::vector<tmx::Property> vec, std::string name);
bool isInSecondVector(std::vector<std::pair<Node *, std::string>> vec, std::string value);

std::vector<tmx::Object> mergeVectors(std::vector<tmx::Object> vec1, std::vector<tmx::Object> vec2);
bool isPointInBox(int x, int y, tmx::Object object);
bool isBoxInBox(tmx::Object object1, tmx::Object object2);
bool isEmpty(std::pair<tmx::Object, std::string> pair);
std::pair<tmx::Object, std::string> isInList(std::vector<std::pair<tmx::Object, std::string>> list, std::string value);

#endif