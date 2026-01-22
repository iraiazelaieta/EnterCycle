#include "text.h"
#include "graphics.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

extern int colorR, colorG, colorB;

// ALDAGAI GLOBALAK (Behin bakarrik kargatzeko)
TTF_Font *fontHandia = 0; // 24px
TTF_Font *fontTxikia = 0; // 14px (Erregistrorako)

void textuaGaitu(void)
{
    if (TTF_Init() < 0)
    {
        printf("Errorea TTF_Init: %s\n", TTF_GetError());
        return;
    }

    // 1. Letra HANDIA kargatu
    fontHandia = TTF_OpenFont("OpenSans-Regular.ttf", 24);
    if (!fontHandia)
    {
        fontHandia = TTF_OpenFont("Debug/OpenSans-Regular.ttf", 24);
    }
    if (!fontHandia)
    {
        printf("ERROREA: OpenSans (Handia) ez da aurkitu.\n");
    }

    // 2. Letra TXIKIA kargatu (Hau falta zen seguruenik!)
    fontTxikia = TTF_OpenFont("OpenSans-Regular.ttf", 14);
    if (!fontTxikia)
    {
        fontTxikia = TTF_OpenFont("Debug/OpenSans-Regular.ttf", 14);
    }
    if (!fontTxikia)
    {
        printf("ERROREA: OpenSans (Txikia) ez da aurkitu.\n");
    }
}

void textuaIdatzi(int x, int y, char *str)
{
    if (!fontHandia || !str || str[0] == '\0')
    {
        return;
    }

    SDL_Renderer *gRenderer = getRenderer();
    SDL_Color textColor = {colorR, colorG, colorB, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(fontHandia, str, textColor);
    if (textSurface)
    {
        SDL_Texture *mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect src = {0, 0, textSurface->w, textSurface->h};
        SDL_Rect dst = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(mTexture);
    }
}

// FUNTZIO OPTIMIZATUA (Ez du fitxategia berriro irekitzen)
void textuaIdatziTxikia(int x, int y, char *str)
{
    // Orain 'fontTxikia' globala erabiltzen dugu
    if (!fontTxikia || !str || str[0] == '\0')
    {
        return;
    }

    SDL_Renderer *gRenderer = getRenderer();
    SDL_Color textColor = {colorR, colorG, colorB, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(fontTxikia, str, textColor);
    if (textSurface)
    {
        SDL_Texture *mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect src = {0, 0, textSurface->w, textSurface->h};
        SDL_Rect dst = {x, y, textSurface->w, textSurface->h}; // Hemen marrazten da
        SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(mTexture);
    }
}

void textuaDesgaitu(void)
{
    if (fontHandia)
    {
        TTF_CloseFont(fontHandia);
    }
    if (fontTxikia)
    {
        TTF_CloseFont(fontTxikia);
    }
    fontHandia = 0;
    fontTxikia = 0;
    // TTF_Quit(); // Normalean sgItxi()-k kudeatzen du, baina hemen utzi daiteke
}