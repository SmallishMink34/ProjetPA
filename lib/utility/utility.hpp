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

#endif