#include "utility.hpp"

int findInVector(std::vector<char> vec, char value) {
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i] == value) {
      return i;
    }
  }
  return -1;
}

std::vector<std::vector<char>> getListOfFile(std::ifstream &file) {
  std::vector<std::vector<char>> list;
  std::string line;
  while(std::getline(file, line)) {
    std::vector<char> vec;
    for(int i = 0; i < line.size(); i++) {
      vec.push_back(line[i]);
    }
    list.push_back(vec);
  }
  return list;
}

int width(std::vector<std::vector<char>> list) {
  int max = 0;
  for(int i = 0; i < list.size(); i++) {
    if(list[i].size() > max) {
      max = list[i].size();
    }
  }
  return max;
}

int height(std::vector<std::vector<char>> list) { return list.size(); }

char getCharAt(std::vector<std::vector<char>> list, int x, int y) {
  if(x < 0 || y < 0 || x >= width(list) || y >= height(list)) {
    return ' ';
  }
  return list[y][x];
}

std::string getRandomElement(std::vector<std::string> vec) {
  int random = rand() % vec.size();
  return vec[random];
}

int getNumverInList(std::vector<char> vec) {
  int number = 0;
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i] >= '0' && vec[i] <= '9') {
      number = number * 10 + (vec[i] - '0');
    }
  }
  return number;
}