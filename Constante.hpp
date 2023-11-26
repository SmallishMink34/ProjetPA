#ifndef DefConst
#define DefConst
#include <SDL2/SDL_ttf.h>

const int Windows_W = 1280;
const int Windows_H = 720;

const float Gravity = 0.25f;
const float scale = 1;  // Probleme tiles deplacements (pour test enlever -0.02)

const int Real_W = Windows_W / scale;
const int Real_H = Windows_H / scale;

const int fps = 60;
const float CameraSpeed = 0.1;
const float JumpStrength = 8.0f;

#endif