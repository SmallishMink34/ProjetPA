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

tmx::Property getPropertyFromName(std::vector<tmx::Property> vec, std::string name) {
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i].getName() == name) {
      return vec[i];
    }
  }
  return tmx::Property();
}

bool isInSecondVector(std::vector<std::pair<Node *, std::string>> vec, std::string value) {
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i].second == value) {
      return true;
    }
  }
  return false;
}

std::vector<tmx::Object> mergeVectors(std::vector<tmx::Object> vec1, std::vector<tmx::Object> vec2) {
  std::vector<tmx::Object> mergedVec;
  mergedVec.reserve(vec1.size() + vec2.size());
  mergedVec.insert(mergedVec.end(), vec1.begin(), vec1.end());
  mergedVec.insert(mergedVec.end(), vec2.begin(), vec2.end());
  return mergedVec;
}

int getSeedFromFile(std::string name) {
  int seed = 0;
  std::ifstream file(name);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      for (char c : line) {
        seed += static_cast<int>(c);
      }
    }
    file.close();
  }
  return seed;
}

int compterLettres(const std::string& texte) {
    int nombreLettres = 0;

    for (char caractere : texte) {
        if (std::isalpha(caractere)) {
            ++nombreLettres;
        }
    }

    return nombreLettres;
}