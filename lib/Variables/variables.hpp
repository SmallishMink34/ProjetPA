#ifndef VARIABLES_HPP
#define VARIABLES_HPP

class Variable {
 public:
  const int Windows_W = 1280;
  const int Windows_H = 720;

  const float Gravity = 0.25f;
  // const float scale = Windows_W/1280.0-0.02; // Probleme tiles deplacements (pour test enlever -0.02)
  float scale = Windows_W / 1280.0 - 0.02;

  int Real_W = Windows_W / scale;
  int Real_H = Windows_H / scale;

  const int fps = 60;
  const float CameraSpeed = 0.1;
  const float JumpStrength = 8.0f;

  void ChangeScale(float scale);
};

#endif