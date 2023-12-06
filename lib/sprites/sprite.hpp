#ifndef DefSprite
#define DefSprite

#include <SDL2/SDL.h>

#include <iostream>

class Sprite {
 public:
  // Constructeur
  Sprite();
  Sprite(std::string lien, int x, int y, int w, int h);
  Sprite(int x, int y, int w, int h);
  // Fonctions
  void Moveto(int x, int y);
  void SetImage(SDL_Texture* Img);
  std::string Getlink();
  SDL_Rect* getRect();
  SDL_Rect* getsrcRect();
  SDL_Texture* GetImg();

  /**
   * @brief Dessine le sprite
   * \param Renderer Le renderer sur lequel dessiner
   */
  void selfDraw(SDL_Renderer* Renderer);

  /**
   * @brief Dessine le sprite
   * \param Renderer Le renderer sur lequel dessiner
   * \param x La position en x
   * \param y La position en y
   */
  void selfDraw(SDL_Renderer* Renderer, int x, int y);

  /**
   * @brief Dessine le sprite
   * \param Renderer Le renderer sur lequel dessiner
   * \param x La position en x
   * \param y La position en y
   * \param Frame Le rectangle de destination
   */
  void selfDraw(SDL_Renderer* Renderer, int x, int y, SDL_Rect Frame);
  /**
   * @brief Dessine le sprite en répétant l'image
   * \param Renderer Le renderer sur lequel dessiner
   * \param w Le nombre de fois à répéter l'image en largeur
   * \param h Le nombre de fois à répéter l'image en hauteur
   * \param dx Le décalage en x
   * \param dy Le décalage en y
   */
  void DrawRepeat(SDL_Renderer* Renderer, int w, int h, int dx, int dy);
  void loadImage(SDL_Renderer* Renderer);
  void loadImage(SDL_Renderer* Renderer, SDL_Texture* Img);
  void setSrcRect(int x, int y, int w, int h);
  int getWidth();
  int getHeight();
  bool isColliding(int x, int y, int w, int h);

 private:
  // Variables
  int x;
  int y;
  int w;
  int h;
  int realw;
  int realh;
  bool Rezise;
  SDL_Rect* rect;
  SDL_Rect* srcRect;
  std::string lien;
  SDL_Texture* Img;
};

#endif