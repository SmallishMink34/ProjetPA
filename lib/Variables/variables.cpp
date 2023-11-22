#include "variables.hpp"


void Variable::ChangeScale(float scale){
    this->scale = scale;
    this->Real_W = this->Windows_W/scale;
    this->Real_H = this->Windows_H/scale;
}