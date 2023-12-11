#ifndef pause_HPP
#define pause_HPP
#include "../gamemode/gamemode.hpp"
#include "../sprites/sprite.hpp"
#include "../button/button.hpp"
#include "../player/player.hpp"
#include <SDL2/SDL.h>

class Mpause : public Gamemode {
    public:
        Sprite Image;
        HUD *Hud;
        Bouton play;
        Bouton exit;
        Bouton main_menu;
        SDL_Event evenement;

        Mpause(SDL_Window* gWindow, SDL_Renderer* gRenderer, Variable* Var);
        void Init();
        void saveScore();
        void handleEvents(std::string* Gamemode);
        void render();
        void update();
        void unpause();
        int Real_W;
        int Real_H;
        bool var;
        bool menu;
        std::string scr;
    private:
        SDL_Rect Message_rect;
        SDL_Texture* TextureMessage;

        SDL_Rect Seed_rect;
        SDL_Texture* TextureSeed;
};

#endif