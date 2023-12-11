#ifndef DefSprite
#define DefSprite

#include <SDL2/SDL.h>

#include <iostream>

class Sprite {
 public:
  /**
   * @brief Default constructor for Sprite class.
   */
  Sprite();

  /**
   * @brief Constructor for Sprite class with image link, position, and size parameters.
   * @param lien The image link.
   * @param x The x-coordinate of the sprite's position.
   * @param y The y-coordinate of the sprite's position.
   * @param w The width of the sprite.
   * @param h The height of the sprite.
   */
  Sprite(std::string lien, int x, int y, int w, int h);

  /**
   * @brief Constructor for Sprite class with position and size parameters.
   * @param x The x-coordinate of the sprite's position.
   * @param y The y-coordinate of the sprite's position.
   * @param w The width of the sprite.
   * @param h The height of the sprite.
   */
  Sprite(int x, int y, int w, int h);

  /**
   * @brief Destructor for Sprite class.
   */
  ~Sprite();

  /**
   * @brief Moves the sprite to the specified position.
   * @param x The new x-coordinate of the sprite's position.
   * @param y The new y-coordinate of the sprite's position.
   */
  void Moveto(int x, int y);

  /**
   * @brief Sets the image of the sprite.
   * @param Img The SDL_Texture representing the image.
   */
  void SetImage(SDL_Texture* Img);

  /**
   * @brief Sets the image of the sprite with the specified image link, position, and size.
   * @param lien The image link.
   * @param x The x-coordinate of the sprite's position.
   * @param y The y-coordinate of the sprite's position.
   * @param w The width of the sprite.
   * @param h The height of the sprite.
   */
  void SetImage(std::string lien, int x, int y, int w, int h);

  /**
   * @brief Gets the image link of the sprite.
   * @return The image link.
   */
  std::string Getlink();

  /**
   * @brief Gets the SDL_Rect representing the sprite's position and size.
   * @return The SDL_Rect representing the sprite's position and size.
   */
  SDL_Rect* getRect();

  /**
   * @brief Gets the SDL_Rect representing the source rectangle of the sprite's image.
   * @return The SDL_Rect representing the source rectangle of the sprite's image.
   */
  SDL_Rect* getsrcRect();

  /**
   * @brief Gets the SDL_Texture representing the sprite's image.
   * @return The SDL_Texture representing the sprite's image.
   */
  SDL_Texture* GetImg();

  /**
   * @brief Draws the sprite on the specified renderer.
   * @param Renderer The SDL_Renderer on which to draw the sprite.
   */
  void selfDraw(SDL_Renderer* Renderer);

  /**
   * @brief Draws the sprite on the specified renderer at the specified position.
   * @param Renderer The SDL_Renderer on which to draw the sprite.
   * @param x The x-coordinate of the position to draw the sprite.
   * @param y The y-coordinate of the position to draw the sprite.
   */
  void selfDraw(SDL_Renderer* Renderer, int x, int y);

  /**
   * @brief Draws the sprite on the specified renderer at the specified position and destination rectangle.
   * @param Renderer The SDL_Renderer on which to draw the sprite.
   * @param x The x-coordinate of the position to draw the sprite.
   * @param y The y-coordinate of the position to draw the sprite.
   * @param Frame The destination rectangle.
   */
  void selfDraw(SDL_Renderer* Renderer, int x, int y, SDL_Rect Frame);

  /**
   * @brief Draws the sprite by repeating the image.
   * @param Renderer The SDL_Renderer on which to draw the sprite.
   * @param w The number of times to repeat the image in width.
   * @param h The number of times to repeat the image in height.
   * @param dx The x-offset for each repeated image.
   * @param dy The y-offset for each repeated image.
   */
  void DrawRepeat(SDL_Renderer* Renderer, int w, int h, int dx, int dy);

  /**
   * @brief Loads the image of the sprite using the specified renderer.
   * @param Renderer The SDL_Renderer used to load the image.
   */
  void loadImage(SDL_Renderer* Renderer);

  /**
   * @brief Loads the image of the sprite using the specified renderer and image.
   * @param Renderer The SDL_Renderer used to load the image.
   * @param Img The SDL_Texture representing the image.
   */
  void loadImage(SDL_Renderer* Renderer, SDL_Texture* Img);

  /**
   * @brief Sets the source rectangle of the sprite's image.
   * @param x The x-coordinate of the source rectangle.
   * @param y The y-coordinate of the source rectangle.
   * @param w The width of the source rectangle.
   * @param h The height of the source rectangle.
   */
  void setSrcRect(int x, int y, int w, int h);

  /**
   * @brief Gets the width of the sprite.
   * @return The width of the sprite.
   */
  int getWidth();

  /**
   * @brief Gets the height of the sprite.
   * @return The height of the sprite.
   */
  int getHeight();

  /**
   * @brief Checks if the sprite is colliding with the specified rectangle.
   * @param x The x-coordinate of the rectangle.
   * @param y The y-coordinate of the rectangle.
   * @param w The width of the rectangle.
   * @param h The height of the rectangle.
   * @return True if the sprite is colliding with the rectangle, false otherwise.
   */
  bool isColliding(int x, int y, int w, int h);

 private:
  // Variables
  int x;             // The x-coordinate of the sprite's position.
  int y;             // The y-coordinate of the sprite's position.
  int w;             // The width of the sprite.
  int h;             // The height of the sprite.
  int realw;         // The actual width of the sprite.
  int realh;         // The actual height of the sprite.
  bool Rezise;       // Flag indicating if the sprite needs to be resized.
  SDL_Rect rect;     // The SDL_Rect representing the sprite's position and size.
  SDL_Rect srcRect;  // The SDL_Rect representing the source rectangle of the sprite's image.
  std::string lien;  // The image link.
  SDL_Texture* Img;  // The SDL_Texture representing the sprite's image.
};
#endif