#include "gamemode.hpp"
// Constructor
Gamemode::Gamemode() {
  gWindow = nullptr;
  gRenderer = nullptr;
  quit = false;
  isLoaded = false;
  Var = nullptr;
}

// Destructor
Gamemode::~Gamemode() {
  gWindow = nullptr;
  gRenderer = nullptr;
  Var = nullptr;
}