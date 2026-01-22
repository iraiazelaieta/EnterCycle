#include "sektoreak.h"
#include "ebentoak.h"
#include "graphics.h"
#include "text.h"
#include <stdio.h>
#include <string.h>

#include "../../fitxeroak/funtzioak.h"
#include "appState.h"


static char *sektoreIzenak[] = {"Diseinu industriala", "Informatika",  "Mekatronika", "Metalurgia", "Lurringintza",
                                "Nekazaritza",         "Abeltzaintza", "Mekanika",    "Elektronika"};

static int erakutsiErrorea = 0;

// ALDAGAI KONSTANTEAK
// Y_HASIERA aldatu dugu zerrenda gorago hasteko (lehen 125 zen)
#define Y_HASIERA 85
#define TARTEA 35

APP_EGOERA sektoreakLogika(SektoreakDatos *datos, int ebentua, ErregistroDatos *regDat, Produktuak *proDat, APP_EGOERA aurrekoEgoera)
{ 
    APP_EGOERA egoera = PANTAILA_SEKTOREAK;

    int error;

    if (ebentua == GERTAERA_IRTEN)
    {
        return PANT_IRTEN;
    }
   
    if (ebentua == SAGU_BOTOIA_EZKERRA)
    {
        POSIZIOA p = saguarenPosizioa();

        // Zirkuluak aukeratu
        for (int i = 0; i < 9; i++)
        {
            int yPos = Y_HASIERA + (i * TARTEA);

            // Klik eremua: Zirkuluaren inguruan
            if (p.x > 150 && p.x < 480 && p.y > (yPos - 15) && p.y < (yPos + 15))
            {
                datos->aukeratuak[i] = !datos->aukeratuak[i]; // Egoera aldatu
                erakutsiErrorea = 0; // Al tocar cualquier sector, quitamos el aviso
            }
        }

        // GORDE ETA JARRAITU BOTOIA (Hau ere 40px igo dugu: 400-440)
        if (p.x > 250 && p.x < 390 && p.y > 400 && p.y < 440)
        {

            int kont = 0;
            for (int i = 0; i < 9; i++)
            {
                if (datos->aukeratuak[i])
                {
                    kont++;
                }
            }
            if (kont == 0)
            {
                erakutsiErrorea = 1;
               // egoera = PANTAILA_SEKTOREAK;
            }
            else{

                erakutsiErrorea = 0;

                if(aurrekoEgoera == PANTAILA_ERREGISTROA)
                {
                    error = EnpresaGehitu(*regDat, *datos);

                    erabiltzailea = bilatuErabiltzaileaById(error);
                }
                if(aurrekoEgoera == PANTAILA_PRODUKTUA)
                {
                    sprintf(proDat->idEmpresa, "%d", erabiltzailea.id);

                    error = gehituProduktuak(*proDat, *datos);

                    GarbituProduktua(proDat);

                }
               //return PANTAILA_JOKOA;
                egoera = PANTAILA_INICIO;
            }
        }
    }
    return egoera;
}

void sektoreakMarraztu(SektoreakDatos *datos)
{
    pantailaGarbitu();

    // 1. Karratu nagusia (Gorago igo dugu: Y=20)
    arkatzKoloreaEzarri(180, 180, 255);                // Urdin argia
    marraztuLaukizuzenBiribila(140, 20, 360, 430, 20); // Y=20tik behera (Lehen 60 zen)

    // 2. Izenburua (Goian zentratuta)
    arkatzKoloreaEzarri(0, 0, 0);
    textuaIdatzi(200, 35, "SEKTOREAK HAUTATU"); // Y=35 (Lehen 75 zen)

    // Erabiltzailearen izena (Grisa, txikiagoa)
    arkatzKoloreaEzarri(80, 80, 80);
    char agurra[100];
    sprintf(agurra, "Erabiltzailea: %s", datos->erabiltzailea);
    textuaIdatziTxikia(160, 60, agurra); // Y=60 (Lehen 100 zen)

    // 3. ZERRENDA MARRAZTU
    for (int i = 0; i < 9; i++)
    {
       
        int yPos = Y_HASIERA + (i * TARTEA);

        // --- ALDAKETA HEMEN: Aukeraketa nabarmenagoa egiteko ---

        if (datos->aukeratuak[i])
        {
            // AUKERATUTA: Berdea eta betea
            arkatzKoloreaEzarri(0, 180, 0); // Berde iluna

            // Zirkulua "bete" egiteko, erradio desberdineko zirkulu asko marrazten ditugu
            for (int r = 0; r <= 12; r++)
            {
                zirkuluaMarraztu(170, yPos, r);
            }

            // Testua ere berdez
            arkatzKoloreaEzarri(0, 100, 0);
            textuaIdatzi(200, yPos - 12, sektoreIzenak[i]);

            // Tick bat (V) marraztu zirkulu barruan (Zuria)
            arkatzKoloreaEzarri(255, 255, 255);
            zuzenaMarraztu(165, yPos, 170, yPos + 5);     // V ezkerra
            zuzenaMarraztu(170, yPos + 5, 175, yPos - 5); // V eskuina
        }
        else
        {
            // EZ AUKERATUTA: Grisa eta hutsik
            arkatzKoloreaEzarri(100, 100, 100); // Gris iluna ertzerako
            zirkuluaMarraztu(170, yPos, 12);

            // Testua beltzez (normal)
            arkatzKoloreaEzarri(0, 0, 0);
            textuaIdatzi(200, yPos - 12, sektoreIzenak[i]);
        }

        // Lerroa azpian (Dekorazioa)
        arkatzKoloreaEzarri(200, 200, 200); // Gris argia
        int luzera = strlen(sektoreIzenak[i]) * 10;
        zuzenaMarraztu(200, yPos + 10, 200 + luzera, yPos + 10);
    }

    // --- LO QUE TE FALTABA: DIBUJAR EL AVISO ---
    if (erakutsiErrorea == 1)
    {
        arkatzKoloreaEzarri(255, 0, 0); // Color Rojo
        textuaIdatziTxikia(235, 300, "Arlo guztiak bete");
    }

    // 4. BOTOIA (Behean, hau ere igo dugu)
    arkatzKoloreaEzarri(50, 50, 255);           // Urdin iluna
    marraztuBotoiBeteaLogin(250, 400, 140, 40); // Y=400 (Lehen 440 zen)

    arkatzKoloreaEzarri(255, 255, 0); // Horia
    textuaIdatzi(275, 405, "GORDE");  // Y=405 (Lehen 445 zen)
}