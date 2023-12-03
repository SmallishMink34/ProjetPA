#include "variables.hpp"

#include <iostream>

void Variable::ChangeScale(float scale) {
  this->scale = scale;
  this->Real_W = Windows_W / scale;
  this->Real_H = Windows_H / scale;
}
