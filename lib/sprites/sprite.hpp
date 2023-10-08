#ifndef DefSprite
#define DefSprite

#include <iostream>
#include <SDL2/SDL.h>

class Sprite{
    public:
        // Constructeur
        Sprite();
        Sprite(std::string lien,int x, int y, int w, int h);

        // Fonctions
        void Moveto(int x, int y);
        void SetImage(SDL_Texture* Img);
        std::string Getlink();
        SDL_Rect* getRect();
        SDL_Rect* getsrcRect();
        SDL_Texture* GetImg();
        void selfDraw(SDL_Renderer* Renderer);
        void loadImage(SDL_Renderer *Renderer);
        void setSrcRect(int x, int y, int w, int h);
        int getWidth();
        int getHeight();

    private:
        // Variables
        int x;
        int y;
        int w;
        int h;
        SDL_Rect* rect;
        SDL_Rect* srcRect;
        std::string lien;
        SDL_Texture* Img;
};


#endif