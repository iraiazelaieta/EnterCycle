// KONPONKETA: Izenak bakarrik
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"

#include "ourTypes.h"
#include "pantailak/erregistroa/erregistroa.h"
#include "pantailak/kudeatuSaskia/kudeatuSaskia.h"
#include "pantailak/login/login.h"
#include "pantailak/produktoak/produktoak.h"
#include "pantailak/sektoreak/sektoreak.h"

#include <SDL.h>
#include <stdio.h>
#include <string.h> // strcpy-rako beharrezkoa

// --- KONSTANTEAK ---
#define TECLA_ENTER 13
#define TECLA_ESCAPE 27
#define NUM_FRAMES 48

#ifndef VELOCIDAD_ANIM
#define VELOCIDAD_ANIM 0
#endif

int main(int argc, char *argv[])
{
    // 1. SDL HASIERATU
    if (sgHasieratu() < 0)
    {
        return -1;
    }

    // 2. TESTUA GAITU
    textuaGaitu();

    // 3. LOGOA KARGATU

    char *irudiIzena = "Debug/img/logo.bmp";
    int logoId = irudiaKargatu(irudiIzena);
    if (logoId != -1)
    {
        irudiaEskalatu(logoId, 300, 80);
        irudiaMugitu(logoId, 170, 50);
        irudiaMugitu(logoId, -1000, -1000); // Hasieran ezkutatu (Animazioagatik)
    }
    else
    {
        printf("OHARRA: Ez da logoa aurkitu.\n");
    }

    //------------- Animazioa ---------------

    /*

    char rutaImagen[100];
    int animId = -1;
    int saltatu = 0;


    for (int i = 0; i < NUM_FRAMES && !saltatu; i++)
    {
        pantailaGarbitu();
        //sprintf(rutaImagen, "../Debug/img/animacion/%d.bmp", i);
        sprintf(rutaImagen, "Debug/img/animacion/%d.bmp", i);
        printf("%d", i);
        animId = irudiaKargatu(rutaImagen);

        if (animId != -1)
        {
            irudiaMugitu(animId, 0, 0);
            irudiaEskalatu(animId, 640, 480);
            irudiakMarraztu();
            pantailaBerriztu();
            SDL_Delay(VELOCIDAD_ANIM);
            irudiaKendu(animId); // Memoria askatu
        }

        int ebentua = ebentuaJasoGertatuBada();
        if (ebentua == SAGU_BOTOIA_EZKERRA || ebentua == TECLA_ENTER)
        {
            saltatu = 1;
        }
    }

    */

    APP_EGOERA egoera = PANTAILA_LOGIN;
    APP_EGOERA aurrekoEgoera = PANTAILA_LOGIN;

    LoginDatos loginDat = {0}; // erabiltzailea | Pasahitza | Pasahitza Izkia | fokua
    ErregistroDatos regDat = {0};
    Produktuak produktuakGehitu = {0};
    SektoreakDatos sektoreDatuak = {0};

    // Inicio pantailako datuak (Grid, Kategoriak, Bilaketa...)
    InicioDatos inicioDatuak = {0};
    inicioDatuakHasieratu(&inicioDatuak);

    DatosProducto datosProducto = {0};

    // SOINUA

    int klikSoinua;
    int erosketaSoinua;

    audioInit();

    erosketaSoinua = loadSound("Debug/sound/audio-erosketa.wav");
    klikSoinua = loadSound("Debug/sound/audio-klik.wav");

    loadTheMusic("Debug/sound/musika.mp3");

    playMusic();

    // APP_EGOERA egoera = PANTAILA_JOKOA;
    int ebentua = 0;

    while (egoera != PANT_IRTEN)
    {
        APP_EGOERA egoeraZaharra = egoera;

        // --- 1. SAGU BIRTUALA KUDEATU ---
        // Funtzio honek koordenatuak (saguPos) eguneratzen ditu W,A,S,D edo geziekin
        saguBirtualaKudeatu();

        ebentua = ebentuaJasoGertatuBada();

        // --- LOGOAREN KUDEAKETA ---
        if (logoId != -1)
        {
            if (egoera == PANTAILA_LOGIN)
            {
                irudiaEskalatu(logoId, 300, 80);
                irudiaMugitu(logoId, 170, 50);
            }
            else if (egoera == PANTAILA_ERREGISTROA || egoera == PANTAILA_SEKTOREAK)
            {
                irudiaEskalatu(logoId, 300, 80);
                irudiaMugitu(logoId, 170, 10);
            }
            else if (egoera == PANTAILA_INICIO || egoera == PANTAILA_SASKIA)
            {
                irudiaEskalatu(logoId, 150, 40);
                irudiaMugitu(logoId, 470, 430);
            }
            else
            {
                irudiaMugitu(logoId, -1000, -1000);
            }
        }

        if (ebentua == SAGU_BOTOIA_EZKERRA)
        {
            playSound(klikSoinua);
        }

        if (ebentua == 109)
        {
            toggleMusic();
        }

        switch (egoera)
        {
        case PANTAILA_LOGIN:

            egoera = loginLogikaManejar(&loginDat, ebentua);
            loginMarraztu(&loginDat);
            if (logoId != -1)
            {
                irudiaMugitu(logoId, 170, 50);
            }
            break;
        case PANTAILA_ERREGISTROA:

            if (logoId != -1)
            {
                irudiaMugitu(logoId, 170, 10);
            }
            egoera = erregistroaLogika(&regDat, ebentua);
            erregistroaMarraztu(&regDat);
            break;
        case PANTAILA_SEKTOREAK:
            // '&' erabili helbidea pasatzeko
            egoera = sektoreakLogika(&sektoreDatuak, ebentua, &regDat, &produktuakGehitu, aurrekoEgoera);
            sektoreakMarraztu(&sektoreDatuak);
            // break;
            break;
        case PANTAILA_PRODUKTUA:

            printf(&datosProducto);
            egoera = ProduktuaGehitu(logoId, &produktuakGehitu, ebentua, &datosProducto);
            marraztuHorria(logoId, &produktuakGehitu, &datosProducto);
            break;
        case PANTAILA_INICIO:

            // datosProducto.modo = MODO_CREAR;

            egoera = inicioLogika(&inicioDatuak, ebentua, &datosProducto);
            inicioMarraztu(&inicioDatuak);

            printf("DEBUG: id orain: %d\n", datosProducto.id);
            printf("DEBUG: precio orain: %f\n", datosProducto.precio);
            printf("DEBUG: cantidad orain: %d\n", datosProducto.cantidad);

            if (egoera == PANTAILA_PRODUKTUA && datosProducto.modo != MODO_VISUALIZAR)
            {
                datosProducto.modo = MODO_CREAR;
                // Izena eta abar garbitu berria denez
                strcpy(datosProducto.nombre, "");
                datosProducto.precio = 0;
                datosProducto.cantidad = 0;
            }
            break;
        case PANTAILA_SASKIA:
            egoera = saskiaLogika(&inicioDatuak, ebentua, erosketaSoinua);
            saskiaMarraztu(&inicioDatuak);
            break;
        default:
            break;
        }

        // Mantén memoria de la pantalla anterior solo cuando realmente
        // cambiamos de pantalla; así, al permanecer en sectores seguiremos
        // sabiendo desde dónde entramos (erregistroa edo produktuak).
        if (egoera != egoeraZaharra)
        {
            aurrekoEgoera = egoeraZaharra;
        }

        // --- KURTSOREA MARRAZTU (Dena marraztu ondoren) ---
        POSIZIOA p = saguarenPosizioa();
        marraztuKurtsorea(p.x, p.y);

        pantailaBerriztu();
        SDL_Delay(10);
        // SDL_Delay(16);
    }

    audioTerminate();

    textuaDesgaitu();
    sgItxi();
    return 0;
}
