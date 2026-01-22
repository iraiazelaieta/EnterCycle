#include "imagen.h"
#include "graphics.h"
#include <SDL.h>
#include <stdio.h>

int irudiarenPosizioaAurkitu(int id);

typedef struct Img
{
    int id;
    SDL_Surface *imagen;
    SDL_Texture *texture;
    SDL_Rect dest;
} IMG;

IMG irudiak[MAX_IMG];
int irudiKop = 0;
int id = 0;

void irudiaMarraztu(SDL_Texture *texture, SDL_Rect *dest)
{
    SDL_Renderer *gRenderer = getRenderer();
    SDL_RenderCopy(gRenderer, texture, NULL, dest);
}

// 2. FUNTZIO BERRIA GEHITU (Izen desberdinarekin: irudiaMarraztuId)
void irudiaMarraztuId(int id, int x, int y)
{
    int i = 0;
    while (i < irudiKop)
    {
        if (irudiak[i].id == id)
        {
            SDL_Rect dest;
            dest.x = x;
            dest.y = y;

            // ZUZENKETA GARRANTZITSUA:
            // Ez erabili 'irudiak[i].imagen->w' (Surface-a agian ezabatuta dago).
            // Horren ordez, galdetu Texturari bere tamaina funtzio honekin:
            SDL_QueryTexture(irudiak[i].texture, NULL, NULL, &dest.w, &dest.h);

            SDL_Renderer *gRenderer = getRenderer();
            SDL_RenderCopy(gRenderer, irudiak[i].texture, NULL, &dest);
            return;
        }
        i++;
    }
}
// ------------------------------------------------------------

int irudiaKargatu(char *fileName)
{
    int colorkey;
    SDL_Surface *surface;
    SDL_Renderer *gRenderer = getRenderer();

    if (irudiKop < MAX_IMG)
    {
        surface = SDL_LoadBMP(fileName);
        if (surface == NULL)
        {
            fprintf(stderr, "Couldn't load %s: %s\n", fileName, SDL_GetError());
            return -1;
        }
        else
        {
            colorkey = SDL_MapRGB(surface->format, 255, 0, 255);
            SDL_SetColorKey(surface, SDL_TRUE, colorkey);
            irudiak[irudiKop].texture = SDL_CreateTextureFromSurface(gRenderer, surface);
            irudiak[irudiKop].dest.x = irudiak[irudiKop].dest.y = 0;
            irudiak[irudiKop].dest.w = surface->w;
            irudiak[irudiKop].dest.h = surface->h;
            SDL_FreeSurface(surface);
            irudiak[irudiKop].id = id;
            irudiKop++;
            id++;
        }
    }
    else
    {
        printf("Has superado el maximo de Imagenes por aplicacion. Para aumentar imagen.h\n");
        return -1;
    }

    return id - 1;
}

void irudiaMugitu(int numImg, int x, int y)
{
    int id = irudiarenPosizioaAurkitu(numImg);
    if (id != -1)
    {
        irudiak[id].dest.x = x;
        irudiak[id].dest.y = y;
    }
}

void irudiaEskalatu(int numImg, int w, int h)
{
    int id = irudiarenPosizioaAurkitu(numImg);
    if (id != -1)
    {
        // Irudiaren destinoaren zabalera eta altuera aldatu
        irudiak[id].dest.w = w;
        irudiak[id].dest.h = h;
    }
}

void irudiakMarraztu(void)
{
    int i = 0;

    for (i = 0; i < irudiKop; i++)
    {
        // Orain funtzio hau existitzen da eta ez du errorerik emango
        irudiaMarraztu(irudiak[i].texture, &irudiak[i].dest);
    }
}

void irudiaKendu(int id)
{
    int i = 0, pos = 0;

    pos = irudiarenPosizioaAurkitu(id);
    if (pos == -1)
    {
        return; // Irudia ez bada existitzen, irten
    }

    SDL_DestroyTexture(irudiak[pos].texture);

    for (i = pos; i < irudiKop - 1; i++) // -1 jarri dugu array-tik ez ateratzeko
    {
        irudiak[i] = irudiak[i + 1];
    }
    irudiKop--;
}

int irudiarenPosizioaAurkitu(int id)
{
    int i = 0;

    for (i = 0; i < irudiKop; i++)
    {
        if (id == irudiak[i].id)
        {
            return i;
        }
    }
    return -1;
}