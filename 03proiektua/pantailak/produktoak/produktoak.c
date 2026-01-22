#include "graphics.h"
#include "imagen.h"
#include "login.h"
#include "text.h"
#include <stdio.h>
#include <string.h>

#include "../../fitxeroak/funtzioak.h"
#include "appState.h"

APP_EGOERA ProduktuaGehitu(int logoId, Produktuak *produktuakGehitu, int ebentua, DatosProducto *datosProducto)
{
    // printf("erabiltzailea: %d\n", erabiltzailea.id);

    if (ebentua == TECLA_RETURN || ebentua == TECLA_ESCAPE)
    {
        GarbituProduktua(datosProducto);

        return PANTAILA_INICIO;

    }

    if (datosProducto->modo == MODO_CREAR)
    {
        if (ebentua == SAGU_BOTOIA_EZKERRA)
        {
            POSIZIOA p = saguarenPosizioa();

            printf("pos: %d %d\n", p.x, p.y);

            if (p.x > 380 && p.x < 600 && p.y > 90 && p.y < 105)
            {
                produktuakGehitu->fokua = 1;
            }
            else if (p.x > 370 && p.x < 450 && p.y > 135 && p.y < 175)
            {
                produktuakGehitu->fokua = 2;
            }
            else if (p.x > 485 && p.x < 545 && p.y > 135 && p.y < 175)
            {
                produktuakGehitu->fokua = 3;
            }
            else if (p.x > 20 && p.x < 570 && p.y > 280 && p.y < 400)
            {
                produktuakGehitu->fokua = 4;
            }
            else if (p.x > 250 && p.x < 390 && p.y > 410 && p.y < 450) //(250, 410, 140, 40
            {
                printf("BIDALI sakatuta. Gordetzen saiatzen...\n");
                printf("erabiltzailea: %d", erabiltzailea.id);

                /*
                int funcionar;

                //produktuakGehitu->idEmpresa = erabiltzailea.id;
                sprintf(produktuakGehitu->idEmpresa, "%d", erabiltzailea.id);

                funcionar = gehituProduktuak(*produktuakGehitu );

                if(funcionar == 1)
                {
                    printf("ERROR");
                } */

                return PANTAILA_SEKTOREAK;
            }
        }
    }

    if (produktuakGehitu->fokua > 0)
    {
        if (ebentua == EBENTU_TESTU_SARRERA)
        {
            if (produktuakGehitu->fokua == 1 && strlen(produktuakGehitu->nombre) < 40)
            {
                strncat(produktuakGehitu->nombre, devolverTextoIntroducido(), 1);
            }

            else if (produktuakGehitu->fokua == 2 && strlen(produktuakGehitu->precio) < 5)
            {
                strncat(produktuakGehitu->precio, devolverTextoIntroducido(), 1);
            }

            else if (produktuakGehitu->fokua == 3 && strlen(produktuakGehitu->cantidad) < 4)
            {
                strncat(produktuakGehitu->cantidad, devolverTextoIntroducido(), 1);
            }

            else if (produktuakGehitu->fokua == 4 && strlen(produktuakGehitu->descripcion) < 250)
            {
                strncat(produktuakGehitu->descripcion, devolverTextoIntroducido(), 1);
            }
        }
        if (ebentua == 8 || ebentua == 127) // Backspace
        {
            if (produktuakGehitu->fokua == 1 && strlen(produktuakGehitu->nombre) > 0)
            {
                produktuakGehitu->nombre[strlen(produktuakGehitu->nombre) - 1] = '\0';
            }
            else if (produktuakGehitu->fokua == 2 && strlen(produktuakGehitu->precio) > 0)
            {
                produktuakGehitu->precio[strlen(produktuakGehitu->precio) - 1] = '\0';
            }
            else if (produktuakGehitu->fokua == 3 && strlen(produktuakGehitu->cantidad) > 0)
            {
                produktuakGehitu->cantidad[strlen(produktuakGehitu->cantidad) - 1] = '\0';
            }
            else if (produktuakGehitu->fokua == 4 && strlen(produktuakGehitu->descripcion) > 0)
            {
                produktuakGehitu->descripcion[strlen(produktuakGehitu->descripcion) - 1] = '\0';
            }
        }
    }

    return PANTAILA_PRODUKTUA;
}

void marraztuHorria(int logoId, Produktuak *produktuakGehitu, DatosProducto *datosProducto)
{
    printf("DEBUG: Modua orain: %d\n", datosProducto->id);
    pantailaGarbitu();

    irudiaKendu(logoId);

    // 1. IRUDIA
    // irudiakMarraztu();

    // Karratua irudiarentzat

    irudiakMarraztu();

    arkatzKoloreaEzarri(0, 0, 0);

    laukizuzenaMarraztu(20, 80, 360, 80, 360, 260, 20, 260); // Irudia

    arkatzKoloreaEzarri(180, 180, 255);

    marraztuLaukizuzenBiribila(20, 280, 550, 120, 20); // Deskribapena
    marraztuLaukizuzenBiribila(370, 135, 80, 40, 10);  // Euro
    marraztuLaukizuzenBiribila(485, 135, 60, 40, 10);  // Kopurua

    textuaGaitu();

    if (datosProducto->modo == MODO_CREAR)
    {
        arkatzKoloreaEzarri(0, 0, 0);
        if (strlen(produktuakGehitu->nombre) == 0)
        {
            textuaIdatzi(380, 80, "Produktoaren izena");
        }
        else
        {
            textuaIdatzi(380, 80, produktuakGehitu->nombre);
        }

        if (strlen(produktuakGehitu->nombre) == 0)
        {
            textuaIdatziTxikia(30, 300, "Deskribapena");
        }
        else
        {
            textuaIdatziTxikia(30, 300, produktuakGehitu->descripcion);
        }

        arkatzKoloreaEzarri(48, 25, 52);

        if (strlen(produktuakGehitu->precio) == 0)
        {
            textuaIdatziTxikia(395, 145, "0 EURO");
        }
        else
        {
            textuaIdatziTxikia(372, 145, produktuakGehitu->precio);
            textuaIdatziTxikia(405, 145, "EURO");
        }

        if (strlen(produktuakGehitu->cantidad) == 0)
        {
            textuaIdatziTxikia(520, 145, "1 u.");
        }
        else
        {
            textuaIdatziTxikia(500, 145, produktuakGehitu->cantidad);
            textuaIdatziTxikia(525, 145, "u.");
        }
    }

    if (datosProducto->modo == MODO_VISUALIZAR)
    {
        char prezioTestua[50];
        char id[50];

        Produktuak produkto = BueltatuProduktuaById(datosProducto->id);

        // Zenbakia testu bihurtu
        sprintf(prezioTestua, "%d", datosProducto->precio);
        sprintf(id, "%d", datosProducto->id);

        arkatzKoloreaEzarri(0, 0, 0);

        textuaIdatzi(380, 80, produkto.nombre);

        textuaIdatziTxikia(30, 300, produkto.descripcion);

        arkatzKoloreaEzarri(48, 25, 52);

        textuaIdatziTxikia(372, 145, produkto.precio);
        textuaIdatziTxikia(405, 145, "EURO");

        textuaIdatziTxikia(500, 145, produkto.cantidad);
        textuaIdatziTxikia(525, 145, "u.");
    }

    /*
    // Botoia
    arkatzKoloreaEzarri(50, 50, 255);
    marraztuBotoiBeteaLogin(250, 410, 140, 40);
    arkatzKoloreaEzarri(255, 255, 0);*/

    if (datosProducto->modo == MODO_VISUALIZAR)
    {
        //  textuaIdatzi(275, 415, "EROSI");
    }
    else
    {
        arkatzKoloreaEzarri(50, 50, 255);
        marraztuBotoiBeteaLogin(250, 410, 140, 40);
        arkatzKoloreaEzarri(255, 255, 0);
        textuaIdatzi(275, 415, "GORDE");
    }

    pantailaBerriztu();
}