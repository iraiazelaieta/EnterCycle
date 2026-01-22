#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h> // Testuak erabiltzen badituzu, hau ere hemen egotea komeni da

// Funtzio orokorrak
int sgHasieratu();
void sgItxi();
void arkatzKoloreaEzarri(int r, int g, int b);
void pantailaGarbitu();
void pantailaBerriztu();

// Oinarrizko marrazketa
void puntuaMarraztu(int x, int y);
void zuzenaMarraztu(int x1, int y1, int x2, int y2);
void zirkuluaMarraztu(int x, int y, int r);

// Renderer-a lortzeko (beste modulu batzuek behar badute)
SDL_Renderer *getRenderer();

// --- FUNTZIO BERRIAK  ---
void marraztuBotoiBeteaLogin(int x, int y, int w, int h);
void marraztuLaukizuzenBiribila(int x, int y, int w, int h, int r);

void laukizuzenaMarraztu(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

void marraztuScroll(int x, int y, int h, int totalHeight, int currentScroll, int viewHeight);

// --- SAGU BIRTUALA ---
void marraztuKurtsorea(int x, int y);



#endif