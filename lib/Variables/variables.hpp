#ifndef VARIABLES_HPP
#define VARIABLES_HPP
#include <iostream>
class Variable {
 public:
  const int Windows_W = 1280;
  const int Windows_H = 720;

  const float Gravity = 0.25f;
  float scale = Windows_W / 1280.0 - 0.02;

  int Real_W = Windows_W / scale;
  int Real_H = Windows_H / scale;

  const int fps = 60;
  float CameraSpeed = 0.1;
  const float DefaultCameraSpeed = 0.1;
  const float JumpStrength = 8.0f;

  void ChangeScale(float scale);
};

const float maxSpeed = 15.0f;

const std::string MAP = "map.txt";
const int nbOneTallMaps = 1;
const int nbTwoTallMaps = 3;

#endif