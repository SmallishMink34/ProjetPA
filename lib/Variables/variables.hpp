#ifndef VARIABLES_HPP
#define VARIABLES_HPP
#include <SDL2/SDL.h>

#include <iostream>

const int Windows_W = 1280;
const int Windows_H = 720;
const float maxSpeed = 15.0f;
class Variable {
 public:
  float scale = Windows_W / 1280.0 - 0.02;

  int Real_W = Windows_W / scale;
  int Real_H = Windows_H / scale;

  float CameraSpeed = 0.1;
  const float DefaultCameraSpeed = 0.1;
  const int fps = 60;
  int score = 0;

  void ChangeScale(float scale);
  void setScore(int score);
  int getScore();
};

const float Gravity = 0.40f;
const int playerSpeed = 8;
const float JumpStrength = 13.0f;
const std::string MAP = "map.txt";
const int nbOneTallMaps = 2;
const int nbTwoTallMaps = 3;

const int tailleCase = 32;
const float InvincibilityTime = 1.0f;
const float RECUL = 15.0f;

const int porteeArme = 50;
const int cadenceArme = 6;
const int degatsArme = 10;

const std::string nomFichier = "monFichier.txt";

////////////////// Couleur
const SDL_Color White = {255, 255, 255};

////////////////// Affichage

#endif