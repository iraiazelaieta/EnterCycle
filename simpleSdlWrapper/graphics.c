#include "graphics.h"
#include <math.h> // Beharrezkoa izan daiteke kalkulu batzuetarako
#include <stdio.h>

// Aldagai globalak
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// Kolore globalak gordetzeko
int colorR = 0, colorG = 0, colorB = 0;

int sgHasieratu()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL ezin izan da hasieratu! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf ezin izan da hasieratu! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    gWindow = SDL_CreateWindow("EnterCycle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (gWindow == NULL)
    {
        printf("Leihoa ezin izan da sortu! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL)
    {
        printf("Renderer ezin izan da sortu! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_RenderSetLogicalSize(gRenderer, 640, 480);
    arkatzKoloreaEzarri(0, 0, 0);

    return 0;
}

void sgItxi()
{
    if (gRenderer != NULL)
    {
        SDL_DestroyRenderer(gRenderer);
    }
    if (gWindow != NULL)
    {
        SDL_DestroyWindow(gWindow);
    }
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    SDL_Quit();
}

void arkatzKoloreaEzarri(int r, int g, int b)
{
    colorR = r;
    colorG = g;
    colorB = b;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void pantailaGarbitu()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
}

void pantailaBerriztu()
{
    SDL_RenderPresent(gRenderer);
}

void puntuaMarraztu(int x, int y)
{
    SDL_RenderDrawPoint(gRenderer, x, y);
}

void zuzenaMarraztu(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

void zirkuluaMarraztu(int x, int y, int r)
{
    int cx = 0;
    int cy = r;
    int d = 3 - 2 * r;

    while (cy >= cx)
    {
        SDL_RenderDrawPoint(gRenderer, x + cx, y + cy);
        SDL_RenderDrawPoint(gRenderer, x - cx, y + cy);
        SDL_RenderDrawPoint(gRenderer, x + cx, y - cy);
        SDL_RenderDrawPoint(gRenderer, x - cx, y - cy);
        SDL_RenderDrawPoint(gRenderer, x + cy, y + cx);
        SDL_RenderDrawPoint(gRenderer, x - cy, y + cx);
        SDL_RenderDrawPoint(gRenderer, x + cy, y - cx);
        SDL_RenderDrawPoint(gRenderer, x - cy, y - cx);

        cx++;
        if (d > 0)
        {
            cy--;
            d = d + 4 * (cx - cy) + 10;
        }
        else
        {
            d = d + 4 * cx + 6;
        }
    }
}

SDL_Renderer *getRenderer()
{
    return gRenderer;
}

// ---------------------------------------------------------
// FORMA BEREZIAK (LOGIN ETA ERREGISTRO PANTALETARAKO)
// ---------------------------------------------------------

// Botoi "pilula" itxurakoak (Login botoientzat)
void marraztuBotoiBeteaLogin(int x, int y, int w, int h)
{
    int r = h / 2;
    // Zati zuzena marraztu
    for (int i = 0; i < h; i++)
    {
        zuzenaMarraztu(x, y + i, x + w, y + i);
    }
    // Alboetako zirkuluerdiak
    for (int dy = -r; dy <= r; dy++)
    {
        for (int dx = -r; dx <= r; dx++)
        {
            if ((dx * dx + dy * dy) <= (r * r))
            {
                puntuaMarraztu(x + dx, y + r + dy);     // Ezkerra
                puntuaMarraztu(x + w + dx, y + r + dy); // Eskuina
            }
        }
    }
}

// Karratu handia ertz biribilduekin (Erregistroko kaxarentzat)
void marraztuLaukizuzenBiribila(int x, int y, int w, int h, int r)
{
    // Erdiko bloke nagusia (zuzena)
    for (int i = r; i < h - r; i++)
    {
        zuzenaMarraztu(x, y + i, x + w, y + i);
    }
    // Goiko eta beheko blokeak (motzagoak)
    for (int i = 0; i < r; i++)
    {
        zuzenaMarraztu(x + r, y + i, x + w - r, y + i);
        zuzenaMarraztu(x + r, y + h - 1 - i, x + w - r, y + h - 1 - i);
    }

    // Izkinak bete (zirkulu laurdenak)
    for (int dy = 0; dy < r; dy++)
    {
        for (int dx = 0; dx < r; dx++)
        {
            if ((dx * dx + dy * dy) <= (r * r))
            {
                puntuaMarraztu(x + r - dx, y + r - dy);         // Goiko-Ezkerra
                puntuaMarraztu(x + w - r + dx, y + r - dy);     // Goiko-Eskuina
                puntuaMarraztu(x + r - dx, y + h - r + dy);     // Beheko-Ezkerra
                puntuaMarraztu(x + w - r + dx, y + h - r + dy); // Beheko-Eskuina
            }
        }
    }
}

//laukizuzunea marraztu:
void laukizuzenaMarraztu(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    zuzenaMarraztu(x1, y1, x2, y2);
    zuzenaMarraztu(x2, y2, x3, y3);
    zuzenaMarraztu(x3, y3, x4, y4);
    zuzenaMarraztu(x4, y4, x1, y1);

}

 //SCROLL

void marraztuScroll(int x, int y, int h, int totalHeight, int currentScroll, int viewHeight)
{
    // 1. Barraren fondo (Track)
    arkatzKoloreaEzarri(220, 220, 220); // Gris argia
    marraztuLaukizuzenBiribila(x, y, 15, h, 5);

    // 2. Kalkulatu "thumb" (mugitzen den zatia) tamaina eta posizioa
    if (totalHeight <= viewHeight)
    {
        return; // Ez da beharrezkoa scroll-a
    }

    float ratio = (float)viewHeight / totalHeight;
    int thumbHeight = (int)(h * ratio);
    if (thumbHeight < 20)
    {
        thumbHeight = 20; // Minimo bat
    }

    float scrollRatio = (float)currentScroll / (totalHeight - viewHeight);
    int thumbY = y + (int)(scrollRatio * (h - thumbHeight));

    // 3. Marraztu "thumb"
    arkatzKoloreaEzarri(150, 150, 150); // Gris ilunagoa
    marraztuLaukizuzenBiribila(x, thumbY, 15, thumbHeight, 5);
}


// --- SAGU BIRUALA ---
void marraztuKurtsorea(int x, int y)
{
    // 1. GORRIA aukeratu eta ALPHA (gardentasuna) tope
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

    // Kurtsorearen tamaina
    int altuera = 20;
    int zabalera = 15;

    // TRIANGELUA BETETZEKO ALGORITMOA
    for (int i = 0; i < altuera; i++)
    {
        int unekoZabalera = zabalera - (i * zabalera / altuera);

        // Lerro horizontala marraztu ezkerretik eskuinera
        SDL_RenderDrawLine(gRenderer, x, y + i, x + unekoZabalera, y + i);
    }

    // Kolorea lehengora itzuli (Segurtasuna)
    SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, 255);
}