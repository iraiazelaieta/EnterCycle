#include "erregistroa.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "text.h"
#include <stdio.h>
#include <string.h>

#include "../../fitxeroak/funtzioak.h"
#include "appState.h"

// --- KONFIGURAZIOA ---
#define TECLA_F1 1073741882
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8

// Pasahitza ikusteko egoera (0 = ezkutuan, 1 = agerian)
static int pasahitzaIkusgai = 0;
static int erakutsiErrorea = 0;

APP_EGOERA erregistroaLogika(ErregistroDatos *datos, int ebentua)
{
    APP_EGOERA egoera = PANTAILA_ERREGISTROA;

    if (ebentua == GERTAERA_IRTEN)
    {
        return PANT_IRTEN;
    }

    // --- SAGUAREN KLIKAK ---
    if (ebentua == SAGU_BOTOIA_EZKERRA)
    {

        POSIZIOA p = saguarenPosizioa();
        // Input kaxen aukeraketa

        // --- BIDALI BOTOIA ---
        if (p.x > 250 && p.x < 390 && p.y > 410 && p.y < 450)
        {
            if (strlen(datos->nif) == 0 || strlen(datos->emaila) == 0 || strlen(datos->enpresaIzena) == 0 || 
            strlen(datos->erabiltzailea) == 0 || strlen(datos->pasahitza) == 0 || strlen(datos->postaKodea) == 0) 
            {
                printf("%d", erakutsiErrorea);
                erakutsiErrorea = 1;
                //return PANTAILA_ERREGISTROA;
                egoera = PANTAILA_ERREGISTROA;
            }
            else{
                int erantzuna = ErabiltzaileaIzenHorrekinBilatu(*datos);

                printf("erantzuna: %d", erantzuna);

                if(erantzuna == 1)
                {
                    //decir q se ha encontrado un nombre con ese usuario
                    erakutsiErrorea = 2;
                }
                else if(!erantzuna){
                    erakutsiErrorea = 0;
                    egoera = PANTAILA_SEKTOREAK;
                }
                else{
                    // DAR ERROR DE FICHERO
                }
             
            }

           // erakutsiErrorea = 0;

            /*
            printf("BIDALI sakatuta. Gordetzen saiatzen...\n");

            int funcionar;

            funcionar = EnpresaGehitu(*datos);

            if(funcionar == -1)
            {
                printf("ERROR");
            }

            erabiltzailea = bilatuProduktoaById(funcionar);
            */

            // return PANTAILA_SEKTOREAK;
        }

        else if (p.x > 140 && p.x < 500)
        {
            if (p.y > 115 && p.y < 150)
            {
                datos->fokua = 1;
            }
            else if (p.y > 160 && p.y < 195)
            {
                datos->fokua = 2;
            }
            else if (p.y > 205 && p.y < 240)
            {
                datos->fokua = 3;
            }
            else if (p.y > 250 && p.y < 285)
            {
                datos->fokua = 4;
            }
            else if (p.y > 295 && p.y < 330)
            {
                datos->fokua = 5;
            }
            else if (p.y > 340 && p.y < 375)
            {
                if (p.x > 380)
                {
                    pasahitzaIkusgai = !pasahitzaIkusgai;
                }
                datos->fokua = 6;
            }
            else
            {
                datos->fokua = 0;
            }
        }

        else
        {
            datos->fokua = 0;
        }
    }

    // --- IDAZKETA LOGIKA ---
    if (datos->fokua > 0)
    {
        char *destino = NULL;
        switch (datos->fokua)
        {
        case 1:
            destino = datos->enpresaIzena;
            break;
        case 2:
            destino = datos->nif;
            break;
        case 3:
            destino = datos->postaKodea;
            break;
        case 4:
            destino = datos->emaila;
            break;
        case 5:
            destino = datos->erabiltzailea;
            break;
        case 6:
            destino = datos->pasahitza;
            break;
        }

        if (destino != NULL)
        {
            int len = strlen(destino);

            if (ebentua == TECLA_F1)
            {
                if (len < 49)
                {
                    strcat(destino, "@");
                }
            }
            else if (ebentua >= 32 && ebentua <= 126)
            {
                erakutsiErrorea = 0;
                if (len < 49)
                {
                    char c = (char)ebentua;
                    strncat(destino, &c, 1);
                }
            }
            else if (ebentua == TECLA_BACKSPACE)
            {
                erakutsiErrorea = 0;
                if (len > 0)
                {
                    destino[len - 1] = '\0';
                }
            }
        } 
    }
    // return PANTAILA_ERREGISTROA;
    return egoera;
}

void erregistroaMarraztu(ErregistroDatos *datos)
{
    pantailaGarbitu();
    irudiakMarraztu();

    // Karratua
    arkatzKoloreaEzarri(150, 180, 255);
    marraztuLaukizuzenBiribila(120, 100, 400, 380, 20);

    char *tituluak[] = {"Enpresaren izena",       "NIF",      "Posta Kodea", "Kontakturako emaila",
                        "Erabiltzailearen izena", "Pasahitza"};
    char *edukia[] = {datos->enpresaIzena, datos->nif,           datos->postaKodea,
                      datos->emaila,       datos->erabiltzailea, datos->pasahitza};

    int yHasi = 135;
    int tartea = 45;

    for (int i = 0; i < 6; i++)
    {
        int yPos = yHasi + (i * tartea);

        // Lerroa
        if (datos->fokua == (i + 1))
        {
            arkatzKoloreaEzarri(255, 255, 255);
        }
        else
        {
            arkatzKoloreaEzarri(80, 80, 200);
        }
        zuzenaMarraztu(140, yPos + 15, 500, yPos + 15);

        // Testuak (Beltza)
        arkatzKoloreaEzarri(0, 0, 0);

        // Hutsik badago -> Titulua
        if (strlen(edukia[i]) == 0)
        {
            textuaIdatzi(140, yPos - 20, tituluak[i]);

            // Oharrak
            if (i == 3)
            {
                textuaIdatzi(390, yPos - 20, "(F1 = @)");
            }
            if (i == 5)
            {
                textuaIdatzi(390, yPos - 20, "(Ikusi)");
            }
        }
        else
        {
            // PASAHITZA BADA
            if (i == 5)
            {
                textuaIdatzi(390, yPos - 20, "(Ikusi)");

                if (pasahitzaIkusgai == 1)
                {
                    // Agerian
                    textuaIdatzi(140, yPos - 20, edukia[i]);
                }
                else
                {
                    // Izartxoak
                    char izarrak[50] = "";
                    int len = strlen(edukia[i]);
                    for (int k = 0; k < len; k++)
                    {
                        strcat(izarrak, "*");
                    }
                    textuaIdatzi(140, yPos - 20, izarrak);
                }
            }
            else
            {
                // Beste eremuak
                textuaIdatzi(140, yPos - 20, edukia[i]);
                if (i == 3)
                {
                    textuaIdatzi(390, yPos - 20, "(F1 = @)");
                }
            }
        }
    }

    if (erakutsiErrorea > 0)
    {
        arkatzKoloreaEzarri(255, 0, 0); // Rojo

        if(erakutsiErrorea == 1)
        {
            //textuaIdatziTxikia(0, 0, "Arlo guztiak bete");
            textuaIdatziTxikia(235, 390, "Arlo guztiak bete");
        }
          if(erakutsiErrorea == 2)
        {
            //textuaIdatziTxikia(0, 0, "Arlo guztiak bete");
            textuaIdatziTxikia(235, 390, "Erabiltzaile izen hori erabilita dago");
        }
      
    }

    // Botoia
    arkatzKoloreaEzarri(50, 50, 255);
    marraztuBotoiBeteaLogin(250, 410, 140, 40);
    arkatzKoloreaEzarri(255, 255, 0);
    textuaIdatzi(290, 415, "BIDALI");
}