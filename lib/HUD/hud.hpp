#ifndef DefHud
#define DefHud
#include "../player/player.hpp"

class Hud {
 public:
  Hud(Player *player);
  ~Hud();
  void draw();
  void update();

 private:
  Player *joueur;
};
#endif