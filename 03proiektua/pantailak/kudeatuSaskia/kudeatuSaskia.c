#include "kudeatuSaskia.h"
#include "ebentoak.h"
#include "graphics.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

#include "../../fitxeroak/funtzioak.h"
#include "appState.h"

// EGOERAK: 0=Zerrenda, 1=Mezua, 2=Pop-up
static int saskiaEgoera = 0;

// --- LAGUNTZA FUNTZIOAK ---

void marraztuCheckbox(int x, int y, int aukeratuta)
{
    arkatzKoloreaEzarri(0, 0, 0);
    zuzenaMarraztu(x, y, x + 20, y);
    zuzenaMarraztu(x, y + 20, x + 20, y + 20);
    zuzenaMarraztu(x, y, x, y + 20);
    zuzenaMarraztu(x + 20, y, x + 20, y + 20);

    if (aukeratuta)
    {
        arkatzKoloreaEzarri(0, 150, 0);
        for (int i = 2; i < 19; i++)
        {
            zuzenaMarraztu(x + i, y + 2, x + i, y + 18);
        }
    }
}


// --- DISEINU BERRIA: BOTOI BELTZA 'X' BATEKIN ---
void marraztuZakarrontzia(int x, int y)
{
    // 1. Fondo Beltza (Laukizuzen biribildua)
    arkatzKoloreaEzarri(0, 0, 0);
    // x eta y zentroa dira, beraz, koordenatuak doitzen ditugu izkinara joateko
    // Tamaina: 30x30 pixel
    marraztuLaukizuzenBiribila(x - 15, y - 15, 30, 30, 5);

    // 2. 'X' Zuria (Ezabatu ikurra)
    arkatzKoloreaEzarri(255, 255, 255);
    // Marra bat: \ 
    zuzenaMarraztu(x - 5, y - 5, x + 5, y + 5);
    // Beste marra: /
    zuzenaMarraztu(x - 5, y + 5, x + 5, y - 5);
}


// Scroll Barra marrazteko funtzioa (Berdina baina saskiarentzat)
void marraztuScrollBatSaskia(int x, int y, int h, int totalHeight, int currentScroll, int viewHeight)
{
    arkatzKoloreaEzarri(220, 220, 220);
    marraztuLaukizuzenBiribila(x, y, 15, h, 5);

    if (totalHeight <= viewHeight)
    {
        return;
    }

    float ratio = (float)viewHeight / totalHeight;
    int thumbHeight = (int)(h * ratio);
    if (thumbHeight < 20)
    {
        thumbHeight = 20;
    }

    float scrollRatio = (float)currentScroll / (totalHeight - viewHeight);
    int thumbY = y + (int)(scrollRatio * (h - thumbHeight));

    arkatzKoloreaEzarri(150, 150, 150);
    marraztuLaukizuzenBiribila(x, thumbY, 15, thumbHeight, 5);
}

void saskiaMarraztu(InicioDatos *datos)
{
    pantailaGarbitu();

    /*
    // 1. FONDO ZURIA
    arkatzKoloreaEzarri(255, 255, 255);
    pantailaGarbitu();
    marraztuBotoiBeteaLogin(0, 0, 640, 480);

    // 2. GOIBURUA (Urdina)
    arkatzKoloreaEzarri(100, 100, 255);
    marraztuLaukizuzenBiribila(10, 10, 620, 50, 10);

    arkatzKoloreaEzarri(255, 255, 255);
    textuaIdatzi(70, 25, "Saskia");

    // 3. ZERRENDA
    int startY = 80;
    int itemHeight = 100;
    int marraztutakoak = 0;

    for (int i = 0; i < datos->kopurua; i++)
    {
        // Kantitatea 0 baino handiagoa bada bakarrik marraztu
        if (datos->kategoriak[i].kantitatea > 0)
        {
            int y = startY + (marraztutakoak * itemHeight);

            // A. IMAGINA (Laukizuzen grisa)
            arkatzKoloreaEzarri(220, 220, 220);
            marraztuLaukizuzenBiribila(30, y, 80, 80, 10);

            // B. TESTUA
            arkatzKoloreaEzarri(0, 0, 0);
            textuaIdatzi(130, y + 10, datos->kategoriak[i].izena);
            arkatzKoloreaEzarri(100, 100, 100);
            textuaIdatziTxikia(135, y + 38, "Produktuaren definizio laburra");

            // C. KONTROLAK (Kaxa urdina)
            arkatzKoloreaEzarri(180, 180, 255);
            marraztuLaukizuzenBiribila(450, y + 20, 100, 40, 15);

            // Minus (-)
            arkatzKoloreaEzarri(100, 100, 255);
            zirkuluaMarraztu(470, y + 40, 12);
            arkatzKoloreaEzarri(255, 255, 255);
            zuzenaMarraztu(465, y + 40, 475, y + 40);

            // Kantitatea
            arkatzKoloreaEzarri(0, 0, 0);
            char qStr[10];
            sprintf(qStr, "%d", datos->kategoriak[i].kantitatea);
            textuaIdatzi(495, y + 28, qStr);

            // Plus (+)
            arkatzKoloreaEzarri(100, 100, 255);
            zirkuluaMarraztu(530, y + 40, 12);
            arkatzKoloreaEzarri(255, 255, 255);
            zuzenaMarraztu(525, y + 40, 535, y + 40);
            zuzenaMarraztu(530, y + 35, 530, y + 45);

            // D. ZAKARRONTZIA (Diseinu berria: Botoi beltza)
            marraztuZakarrontzia(590, y + 40);

            marraztutakoak++;
        }
    }

    */

    // OHARRA: Scroll barra hemen zegoen, KENDUTA.

    // --- 1. EGOERA: EROSKETA BURUTU MEZUA ---
    if (saskiaEgoera == 1)
    {
        arkatzKoloreaEzarri(0, 0, 0);
        marraztuLaukizuzenBiribila(158, 178, 324, 124, 20);
        arkatzKoloreaEzarri(255, 255, 255);
        marraztuLaukizuzenBiribila(160, 180, 320, 120, 20);
        arkatzKoloreaEzarri(0, 150, 0);
        textuaIdatzi(210, 210, "EROSKETA BURUTU DA!");
        arkatzKoloreaEzarri(100, 100, 100);
        textuaIdatziTxikia(230, 250, "Sakatu edonon jarraitzeko");
        return;
    }

    // --- 2. EGOERA: SASKIA IKUSI ---

    arkatzKoloreaEzarri(255, 255, 255);
    marraztuBotoiBeteaLogin(0, 0, 640, 480);

    // ZERRENDA
    int startY = 80;
    int itemHeight = 100;
    int marraztutakoak = 0;
    float prezioTotala = 0.0;
    int produktuKantitateaTotala = 0;
    int totalContentHeight = 0; // Edukiaren altuera osoa kalkulatzeko

    // Lehenengo buelta: edukiaren tamaina osoa kalkulatu scroll barrarako
    for (int i = 0; i < datos->kopurua; i++)
    {
        if (datos->kategoriak[i].kantitatea > 0)
        {
            totalContentHeight += itemHeight;
        }
    }
    // Gehi marjina batzuk
    totalContentHeight += startY + 100;

    for (int i = 0; i < datos->kopurua; i++)
    {
        if (datos->kategoriak[i].kantitatea > 0)
        {
            float lerroPrezioa = datos->kategoriak[i].prezioa * datos->kategoriak[i].kantitatea;

            if (datos->kategoriak[i].aukeratuta)
            {
                prezioTotala += lerroPrezioa;
                produktuKantitateaTotala++;
            }

            int y = startY + (marraztutakoak * itemHeight) - datos->saskiaScroll;

            // Bakarrik marraztu bistakoak
            if (y > -100 && y < 480)
            {
                // Elementuak pixka bat estuagoak (580px) barrarentzat tokia uzteko
                arkatzKoloreaEzarri(220, 220, 220);
                marraztuLaukizuzenBiribila(20, y, 580, 80, 10);

                marraztuCheckbox(35, y + 30, datos->kategoriak[i].aukeratuta);

                arkatzKoloreaEzarri(200, 200, 200);
                marraztuLaukizuzenBiribila(70, y + 10, 60, 60, 5);

                arkatzKoloreaEzarri(0, 0, 0);
                textuaIdatzi(150, y + 15, datos->kategoriak[i].izena);

                arkatzKoloreaEzarri(50, 50, 50);
              
                char prezioStr[50];
                sprintf(prezioStr, "%.2f x %d = %.2f E", datos->kategoriak[i].prezioa, datos->kategoriak[i].kantitatea,
                        lerroPrezioa);
                textuaIdatziTxikia(150, y + 45, prezioStr);

                int controlsY = y + 30;
                // Kontrolak ere pixka bat ezkerrerago mugitu
                arkatzKoloreaEzarri(180, 180, 255);
                marraztuLaukizuzenBiribila(430, controlsY, 100, 40, 15);

                arkatzKoloreaEzarri(100, 100, 255);
                zirkuluaMarraztu(450, controlsY + 20, 12);
                arkatzKoloreaEzarri(255, 255, 255);
                zuzenaMarraztu(445, controlsY + 20, 455, controlsY + 20);

                arkatzKoloreaEzarri(0, 0, 0);
                char qStr[10];
                sprintf(qStr, "%d", datos->kategoriak[i].kantitatea);
                textuaIdatzi(475, controlsY + 8, qStr);

                //arkatzKoloreaEzarri(100, 100, 255);
                if (datos->kategoriak[i].kantitatea >= datos->kategoriak[i].kopuruTotala)
                {
                    arkatzKoloreaEzarri(180, 180, 180); // Gris si está bloqueado
                }
                else
                {
                    arkatzKoloreaEzarri(100, 100, 255); // Azul (tu color original) si hay stock
                }
                zirkuluaMarraztu(510, controlsY + 20, 12);
                arkatzKoloreaEzarri(255, 255, 255);
                zuzenaMarraztu(505, controlsY + 20, 515, controlsY + 20);
                zuzenaMarraztu(510, controlsY + 15, 510, controlsY + 25);

                marraztuZakarrontzia(560, controlsY + 20);
            }
            marraztutakoak++;
        }
    }

    /*
      // Lógica de dibujo del botón "+"
                if (datos->kategoriak[i].kantitatea >= datos->kategoriak[i].kopuruTotala) 
                {
                    arkatzKoloreaEzarri(180, 180, 180); // Color GRIS (bloqueado)
                } 
                else 
                {
                    arkatzKoloreaEzarri(0, 200, 0); // Color VERDE (disponible)
                }
                    */

    // Maskarak
    arkatzKoloreaEzarri(255, 255, 255);
    marraztuBotoiBeteaLogin(0, 0, 640, 79);
    marraztuBotoiBeteaLogin(0, 400, 640, 80);

    // Goiburua
    arkatzKoloreaEzarri(100, 100, 255);
    marraztuLaukizuzenBiribila(10, 10, 620, 50, 10);
    arkatzKoloreaEzarri(255, 255, 255);
    textuaIdatzi(70, 25, "Saskia");

    // SCROLL BARRA (X=610, Y=80, H=320)
    marraztuScrollBatSaskia(610, 80, 320, totalContentHeight, datos->saskiaScroll, 320);

    // Oina
    if (marraztutakoak > 0)
    {
        arkatzKoloreaEzarri(200, 200, 200);
        zuzenaMarraztu(10, 400, 630, 400);

        char totalStr[50];
        sprintf(totalStr, "GUZTIRA: %.2f E", prezioTotala);
        arkatzKoloreaEzarri(0, 0, 0);
        textuaIdatzi(40, 420, totalStr);

        arkatzKoloreaEzarri(0, 180, 0);
        marraztuBotoiBeteaLogin(450, 410, 140, 45);
        arkatzKoloreaEzarri(255, 255, 255);
        textuaIdatzi(475, 420, "ORDAINDU");
    }

    // --- 3. EGOERA: KONFIRMAZIO LEIHOA (Pop-up) ---
    if (saskiaEgoera == 2)
    {
        arkatzKoloreaEzarri(50, 50, 50);
        marraztuLaukizuzenBiribila(98, 58, 444, 344, 10);
        arkatzKoloreaEzarri(245, 245, 245);
        marraztuLaukizuzenBiribila(100, 60, 440, 340, 10);

        arkatzKoloreaEzarri(0, 0, 0);
        textuaIdatzi(210, 80, "EROSKETA BAIEZTATU");

        arkatzKoloreaEzarri(200, 200, 200);
        zuzenaMarraztu(120, 110, 520, 110);

        int listY = 130;
        int count = 0;
        for (int i = 0; i < datos->kopurua; i++)
        {
            if (datos->kategoriak[i].kantitatea > 0 && datos->kategoriak[i].aukeratuta)
            {
                if (count < 5)
                {
                    char itemStr[60];
                    sprintf(itemStr, "- %s (x%d)", datos->kategoriak[i].izena, datos->kategoriak[i].kantitatea);
                    arkatzKoloreaEzarri(0, 0, 0);
                    textuaIdatziTxikia(130, listY, itemStr);

                    char desc[60];
                    sprintf(desc, "  %.2f E", datos->kategoriak[i].prezioa * datos->kategoriak[i].kantitatea);
                    arkatzKoloreaEzarri(100, 100, 100);
                    textuaIdatziTxikia(350, listY, desc);

                    listY += 25;
                    count++;
                }
            }
        }
        if (produktuKantitateaTotala > 5)
        {
            textuaIdatziTxikia(130, listY, "... eta gehiago.");
        }

        char totalMsg[50];
        sprintf(totalMsg, "GUZTIRA: %.2f E", prezioTotala);
        arkatzKoloreaEzarri(0, 0, 0);
        textuaIdatzi(220, 300, totalMsg);

        arkatzKoloreaEzarri(200, 200, 200);
        marraztuLaukizuzenBiribila(190, 340, 100, 40, 10);
        arkatzKoloreaEzarri(0, 0, 0);
        textuaIdatzi(215, 350, "UTZI");

        arkatzKoloreaEzarri(0, 180, 0);
        marraztuLaukizuzenBiribila(310, 340, 140, 40, 10);
        arkatzKoloreaEzarri(255, 255, 255);
        textuaIdatzi(345, 350, "ONARTU");
    }
}

APP_EGOERA saskiaLogika(InicioDatos *datos, int ebentua, int erosketaSoinua)
{

    /*
    if (ebentua == SAGU_BOTOIA_ESKUINA || ebentua == TECLA_ESCAPE)
    {
        return PANTAILA_INICIO;
    }*/

    if (saskiaEgoera == 1)
    {
        if (ebentua == SAGU_BOTOIA_EZKERRA || ebentua == TECLA_RETURN || ebentua == TECLA_ESCAPE)
        {
            saskiaEgoera = 0;
            return PANTAILA_INICIO;
        }
        return PANTAILA_SASKIA;
    }

    /*
    if (ebentua == SAGU_BOTOIA_EZKERRA)
    {
        POSIZIOA p = saguarenPosizioa();
        int startY = 80;
        int itemHeight = 100;
        int marraztutakoak = 0;

        for (int i = 0; i < datos->kopurua; i++)
        {
            if (datos->kategoriak[i].kantitatea > 0)
            {
                int y = startY + (marraztutakoak * itemHeight);

                // Minus botoia
                if (p.x > 458 && p.x < 482 && p.y > y + 28 && p.y < y + 52)
                {
                    if (datos->kategoriak[i].kantitatea > 0)
                    {
                        datos->kategoriak[i].kantitatea--;
                        datos->saskiaKop--;
                    }
                }
                // Plus botoia
                else if (p.x > 518 && p.x < 542 && p.y > y + 28 && p.y < y + 52)
                {
                    datos->kategoriak[i].kantitatea++;
                    datos->saskiaKop++;
                }
                // Zakarrontzia (Ezabatu)
                else if (p.x > 575 && p.x < 605 && p.y > y + 25 && p.y < y + 55)
                {
                    datos->saskiaKop -= datos->kategoriak[i].kantitatea;
                    datos->kategoriak[i].kantitatea = 0;
                }

                marraztutakoak++;
            }
        }
    }
    return PANTAILA_SASKIA;*/

     if (saskiaEgoera == 2)
    {
        if (ebentua == SAGU_BOTOIA_EZKERRA)
        {
            POSIZIOA p = saguarenPosizioa();

            // UTZI
            if (p.x > 190 && p.x < 290 && p.y > 340 && p.y < 380)
            {
                saskiaEgoera = 0;
            }
            // ONARTU
            else if (p.x > 310 && p.x < 450 && p.y > 340 && p.y < 380)
            {

                playMusic;           
                playSound(erosketaSoinua);

                erosketaGorde(erabiltzailea.id, *datos);

                for (int i = 0; i < datos->kopurua; i++)
                {
                    if (datos->kategoriak[i].kantitatea > 0 && datos->kategoriak[i].aukeratuta)
                    {
                        datos->saskiaKop -= datos->kategoriak[i].kantitatea;
                        datos->kategoriak[i].kantitatea = 0;
                        datos->kategoriak[i].aukeratuta = 0;
                    }
                }
                saskiaEgoera = 1;
                datos->saskiaScroll = 0;
            }
        }
        if (ebentua == TECLA_ESCAPE)
        {
            saskiaEgoera = 0;
        }
        return PANTAILA_SASKIA;
    }

    if (ebentua == SAGU_BOTOIA_ESKUINA || ebentua == TECLA_ESCAPE)
    {
        return PANTAILA_INICIO;
    }

    // Kalkulatu maxScroll logikarako
    int itemHeight = 100;
    int totalContentHeight = 80 + 100; // Margina
    for (int i = 0; i < datos->kopurua; i++)
    {
        if (datos->kategoriak[i].kantitatea > 0)
        {
            totalContentHeight += itemHeight;
        }
    }
    int maxScroll = totalContentHeight - 320; // 320 = ViewHeight
    if (maxScroll < 0)
    {
        maxScroll = 0;
    }

    if (ebentua == TECLA_DOWN)
    {
        datos->saskiaScroll += 20;
        if (datos->saskiaScroll > maxScroll)
        {
            datos->saskiaScroll = maxScroll;
        }
    }
    if (ebentua == TECLA_UP)
    {
        datos->saskiaScroll -= 20;
        if (datos->saskiaScroll < 0)
        {
            datos->saskiaScroll = 0;
        }
    }

    if (ebentua == SAGU_BOTOIA_EZKERRA)
    {
        POSIZIOA p = saguarenPosizioa();

        // SCROLL BARRA (X > 610)
        if (p.x > 610 && p.x < 630 && p.y > 80 && p.y < 400)
        {
            int barHeight = 320;
            int relativeY = p.y - 80;
            float percentage = (float)relativeY / barHeight;
            datos->saskiaScroll = (int)(percentage * maxScroll);
            if (datos->saskiaScroll < 0)
            {
                datos->saskiaScroll = 0;
            }
            if (datos->saskiaScroll > maxScroll)
            {
                datos->saskiaScroll = maxScroll;
            }
        }

        // ORDAINDU BOTOIA
        else if (datos->saskiaKop > 0 && p.x > 450 && p.x < 590 && p.y > 410 && p.y < 455)
        {
            int zerbaitAukeratuta = 0;
            for (int i = 0; i < datos->kopurua; i++)
            {
                if (datos->kategoriak[i].kantitatea > 0 && datos->kategoriak[i].aukeratuta)
                {
                    zerbaitAukeratuta = 1;
                    break;
                }
            }
            if (zerbaitAukeratuta)
            {
                saskiaEgoera = 2;
            }
            return PANTAILA_SASKIA;
        }
        else if (p.y > 80 && p.y < 400 && p.x < 610) // Elementuak
        {
            int startY = 80;
            int marraztutakoak = 0;
            for (int i = 0; i < datos->kopurua; i++)
            {
                if (datos->kategoriak[i].kantitatea > 0)
                {
                    int y = startY + (marraztutakoak * itemHeight) - datos->saskiaScroll;
                    int controlsY = y + 30;

                    if (y > 60 && y < 400)
                    {
                        if (p.x > 30 && p.x < 60 && p.y > y + 25 && p.y < y + 55)
                        {
                            datos->kategoriak[i].aukeratuta = !datos->kategoriak[i].aukeratuta;
                        }
                        else if (p.x > 438 && p.x < 462 && p.y > controlsY + 8 && p.y < controlsY + 32)
                        {
                            if (datos->kategoriak[i].kantitatea > 0)
                            {
                                datos->kategoriak[i].kantitatea--;
                                datos->saskiaKop--;
                            }
                        }
                        else if (p.x > 498 && p.x < 522 && p.y > controlsY + 8 && p.y < controlsY + 32)
                        {
                            if(datos->kategoriak[i].kopuruTotala > datos->kategoriak[i].kantitatea)
                            {
                                datos->kategoriak[i].kantitatea++;
                                datos->saskiaKop++;
                            }
                        }
                        else if (p.x > 545 && p.x < 575 && p.y > controlsY + 5 && p.y < controlsY + 35)
                        {
                            datos->saskiaKop -= datos->kategoriak[i].kantitatea;
                            datos->kategoriak[i].kantitatea = 0;
                        }
                    }
                    marraztutakoak++;
                }
            }
        }
    }
    return PANTAILA_SASKIA;
}