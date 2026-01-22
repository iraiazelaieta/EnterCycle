#include "login.h"
#include "graphics.h"
#include "imagen.h"
#include "text.h"
#include <stdio.h>
#include <string.h>

#include "../../fitxeroak/funtzioak.h"
#include "appState.h"


// ALDAGAI GLOBALA: Pasahitza ikusteko (0 = ezkutuan, 1 = agerian)
static int pasahitzaIkusgai = 0;
static int erakutsiErrorea = 0;


APP_EGOERA loginLogikaManejar(LoginDatos *datos, int ebentua)
{
    if (ebentua == GERTAERA_IRTEN)
    {
        return PANT_IRTEN;
    }
    // --- ENTER DETEKTATU (FITXATEGIA IRAKURRI) ---
    if (ebentua == 13)
    {
      //  int aurkitua = 0;

         printf("DEBUG: Enter klik egin dau\n"); // Si esto no sale en consola, el 13 está mal.
        if (strlen(datos->erabiltzailea) == 0 || strlen(datos->pasahitza) == 0)
        {
            printf("DEBUG: Arloa hutsik dago\n");
            erakutsiErrorea = 1;
            return PANTAILA_LOGIN;
        }
        // Si llegamos aquí, los campos están llenos
        // ... (resto de tu código de lectura de archivo) ...
        erakutsiErrorea = 0;
        int aurkitua = 0;
        char fitxategiUser[100], fitxategiPass[100];

        printf("%s %s\n", datos->erabiltzailea, datos->pasahitza);

        aurkitua = login(*datos);

        // 3. Emaitza egiaztatu
        if (aurkitua > 0)
        {
            printf("Login zuzena! Ongi etorri %s.\n", datos->erabiltzailea);

            erabiltzailea.id = aurkitua;

            erabiltzailea = bilatuErabiltzaileaById(erabiltzailea.id);

            return PANTAILA_INICIO;
            //return PANTAILA_PRODUKTUA;
        }
        else if(aurkitua == -1)
        {
            printf("Login okerra. Saiatu berriro.\n");
            erakutsiErrorea = 2;
            strcpy(datos->pasahitza, "");
            strcpy(datos->pasahitzaIzk, "");
        }
        else{
            return 1;
        }
    }

    // --- SAGUAREN KLIKAK ---
    if (ebentua == SAGU_BOTOIA_EZKERRA)
    {
        POSIZIOA p = saguarenPosizioa();

        // 1. Erabiltzailea kutxa
        if (p.x > 220 && p.x < 420 && p.y > 180 && p.y < 230)
        {
            datos->fokua = 1;
        }
        // 2. Pasahitza kutxa
        else if (p.x > 220 && p.x < 420 && p.y > 240 && p.y < 290)
        {
            // ALDAKETA: Begiratu ea eskuinean (Begia) klik egin duen
            if (p.x > 380)
            {
                pasahitzaIkusgai = !pasahitzaIkusgai; // Egoera aldatu
                datos->fokua = 2;                     // Fokua mantendu
            }
            else
            {
                datos->fokua = 2;
            }
        }

        // KONTUA SORTU ESTEKA
        else if (p.x > 180 && p.x < 460 && p.y > 320 && p.y < 360)
        {
            return PANTAILA_ERREGISTROA;
            //ebentua = PANTAILA_ERREGISTROA;
        }
        else
        {
            datos->fokua = 0;
        }
    }

    // --- IDAZKETA ---
    if (datos->fokua > 0)
    {
        if ((ebentua >= 32 && ebentua <= 126) || ebentua == 8)
        {
            erakutsiErrorea = 0;
        }
        
        if (ebentua == EBENTU_TESTU_SARRERA)
        {
             if (datos->fokua == 1 && strlen(datos->erabiltzailea) < 18)
            {
                strncat(datos->erabiltzailea, devolverTextoIntroducido(), 1);
            }
             
            else if (datos->fokua == 2 && strlen(datos->pasahitza) < 5)
            {
                strncat(datos->pasahitza, devolverTextoIntroducido(), 1);
                strcat(datos->pasahitzaIzk, "*");
            }
        }
        if (ebentua == 8 || ebentua == 127) // Backspace
        {
            if (datos->fokua == 1 && strlen(datos->erabiltzailea) > 0)
            {
                datos->erabiltzailea[strlen(datos->erabiltzailea) - 1] = '\0';
            }
            else if (datos->fokua == 2 && strlen(datos->pasahitza) > 0)
            {
                datos->pasahitza[strlen(datos->pasahitza) - 1] = '\0';
                datos->pasahitzaIzk[strlen(datos->pasahitzaIzk) - 1] = '\0';
            }
        }
    }
    return PANTAILA_LOGIN;
}

void loginMarraztu(LoginDatos *datos)
{
    pantailaGarbitu();

    // 1. IRUDIA
    irudiakMarraztu();

    // 2. ERABILTZAILEA BOTOIA
    if (datos->fokua == 1)
    {
        arkatzKoloreaEzarri(80, 110, 255);
    }
    else
    {
        arkatzKoloreaEzarri(100, 130, 255);
    }
    marraztuBotoiBeteaLogin(220, 180, 200, 50);

    // 3. PASAHITZA BOTOIA
    if (datos->fokua == 2)
    {
        arkatzKoloreaEzarri(80, 110, 255);
    }
    else
    {
        arkatzKoloreaEzarri(100, 130, 255);
    }
    marraztuBotoiBeteaLogin(220, 240, 200, 50);

    // 4. TESTUAK
    arkatzKoloreaEzarri(255, 255, 0);

    // Erabiltzailea testua
    if (strlen(datos->erabiltzailea) == 0)
    {
        textuaIdatzi(250, 195, "Erabiltzailea");
    }
    else
    {
        textuaIdatzi(250, 195, datos->erabiltzailea);
    }

    // Pasahitza testua (BEGIAREN LOGIKA)
    if (strlen(datos->pasahitza) == 0)
    {
        textuaIdatzi(275, 255, "Pasahitza");
        textuaIdatziTxikia(385, 255, "(Ikusi)"); // Botoia erakutsi
    }
    else
    {
        // "Begia" botoia beti marraztu
        textuaIdatziTxikia(385, 255, "(Ikusi)");

        if (pasahitzaIkusgai == 1)
        {
            // Agerian badago -> Testu normala
            textuaIdatzi(275, 255, datos->pasahitza);
        }
        else
        {
            // Ezkutuan badago -> Izartxoak
            textuaIdatzi(275, 255, datos->pasahitzaIzk);
        }
    }

        // --- LO QUE TE FALTABA: DIBUJAR EL AVISO ---
    if(erakutsiErrorea > 0)
    {
        arkatzKoloreaEzarri(255, 0, 0); // Color Rojo
        if (erakutsiErrorea == 1)
        {
            textuaIdatziTxikia(235, 300, "Arlo guztiak bete");
        }
        if (erakutsiErrorea == 2)
        {
            textuaIdatziTxikia(235, 300, "Erabiltzaile edo pasahitz okerra");
        }
    }
   

    // 5. AZPIKO ALDEA (KONTUA SORTU)
    arkatzKoloreaEzarri(0, 80, 255); // Urdina
    textuaIdatziTxikia(280, 335, "Kontua sortu");
    zuzenaMarraztu(180, 345, 265, 345); // Ezkerra
    zuzenaMarraztu(375, 345, 460, 345); // Eskuina

   // pantailaBerriztu();

}