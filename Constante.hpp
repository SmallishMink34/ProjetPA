#ifndef DefConst
#define DefConst

const int Windows_W = 1920;
const int Windows_H = 1080;

const int Gravity = 9;
const float scale = Windows_W/1280.0-0.02; // Probleme tiles deplacements (pour test enlever -0.02)

const int Real_W = Windows_W/scale;
const int Real_H = Windows_H/scale;

const int fps = 144;

#endif