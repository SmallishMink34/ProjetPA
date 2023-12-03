#ifndef defutility
#define defutility
#include <fstream>
#include <iostream>
#include <vector>

int findInVector(std::vector<char> vec, char value);
std::vector<std::vector<char>> getListOfFile(std::ifstream &file);

int width(std::vector<std::vector<char>> list);
int height(std::vector<std::vector<char>> list);

char getCharAt(std::vector<std::vector<char>> list, int x, int y);

std::string getRandomElement(std::vector<std::string> vec);

int getNumverInList(std::vector<char> vec);

#endif