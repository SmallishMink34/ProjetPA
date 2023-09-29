#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"

int main(int argc, char *argv[])
{
    SDL_Window *fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    if (fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("src/arial.ttf",28);

    SDL_Renderer *ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *fond = charger_image("src/fond.bmp", ecran);

    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture *obj = charger_image_transparente("src/obj.bmp", ecran, r, g, b);

    int w, h;
    SDL_QueryTexture(obj, NULL, NULL, &w, &h);

    SDL_Rect SrcR, DestR;
    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = w; // Largeur de l’objet en pixels de la texture
    SrcR.h = h; // Hauteur de l’objet en pixels de la texture
    DestR.x = 350;
    DestR.y = 350;
    DestR.w = w / 3;
    DestR.h = h / 3;


    Uint8 r1 = 0, g1 = 255, b1 = 255;
    SDL_Texture *sprite = charger_image_transparente("src/sprites.bmp", ecran, r1, g1, b1);
    int tailleW, tailleH;

    SDL_QueryTexture(sprite, NULL, NULL, &tailleW, &tailleH);

    SDL_Rect rectSprite[6];
    for(int i=0; i<6; i++)
    {
        rectSprite[i].x = 0;
        rectSprite[i].y = 0;
        rectSprite[i].w = tailleW/3; // Largeur du sprite
        rectSprite[i].h = tailleH/2; // Hauteur du sprite
    }

    SDL_Rect DestR_sprite[6];
    for(int i=0; i<6; i++)
    {
        DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
        DestR_sprite[i].y = i > 2 ? 60 : 120;
        DestR_sprite[i].w = tailleW/3; // Largeur du sprite
        DestR_sprite[i].h = tailleH/2; // Hauteur du sprite
    }

    SDL_Color color = {0,0,0,0};
    char msg[] = "TP sur Makefile et SDL";
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    int texteW, texteH;
    SDL_QueryTexture(texte, NULL, NULL, &texteW, &texteH);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = texteW; // Largeur du texte en pixels (à récupérer)
    text_pos.h = texteH; // Hauteur du texte en pixels (à récupérer)

    // Boucle principale
    while (!terminer)
    {
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        SDL_RenderCopy(ecran, obj, &SrcR, &DestR);
        for(int i=0; i<6; i++)
        {
            SDL_RenderCopy(ecran, sprite, &rectSprite[i], &DestR_sprite[i]);
        }
        SDL_RenderCopy(ecran,texte,NULL,&text_pos);
        while (SDL_PollEvent(&evenements))
        {
            switch (evenements.type)
            {
            case SDL_QUIT:
                terminer = true;
                break;
            }
        }

        SDL_RenderPresent(ecran);
    }
    // Libérer de la mémoire
    SDL_DestroyTexture(fond);
    TTF_CloseFont( font );
    TTF_Quit();
    SDL_DestroyRenderer(ecran);
    return 0;
}