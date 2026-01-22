#include "inicio.h"
#include "ebentoak.h"
#include "graphics.h"
#include "text.h"
#include <SDL.h>
#include <stdio.h>
#include <string.h> // strlen erabiltzeko

#include "../../fitxeroak/funtzioak.h"
#include "appState.h"

extern Erabiltzailea erabiltzailea;


#define GRID_X 50
#define GRID_Y 130
#define BOX_SIZE 150
#define GAP 30
#define COLUMNS 3
#define KLIK_TARTEA 180

/*
int cargarProductosUsuario(Produktuak **miLista) {

    //Produktuak *miLista = NULL;
    
    // Suponiendo que erabiltzailea.sectores es un array de 9 ints (0 o 1)
    // Extraemos solo los IDs de los sectores que el usuario TIENE (los que son 1)
    int sectoresVips[9];
    int nVips = 0;
    
    for(int i = 0; i < 9; i++) {
        if(erabiltzailea.sektoreak[i] == 1) {
            sectoresVips[nVips++] = i; // Guardamos el ID del sector
        }
    }

    // Llamamos a la función de ficheros pasando el filtro
    int total = BueltatuListaProduktuakSektoreka(miLista, sectoresVips, nVips);
    
    // Ahora miLista solo tiene productos de interés para el usuario

    return total;
}*/

void inicioDatuakHasieratu(InicioDatos *datos)
{
    // datos->kopurua = 9;
    datos->saskiaKop = 0;
    datos->klikatutakoId = -1;
    datos->azkenKlikOrdua = 0;
    datos->trantsizioaZain = 0;

    // Bilaketa hasieratu
    strcpy(datos->bilaketa, "");
    datos->idazten = 0;

    // SCROLL HASIERAKETAK
    datos->saskiaScroll = 0;
    datos->inicioScroll = 0;

    // Produktoak

    // Produktuak produktoa =  BueltatuProduktuak();

    
    Produktuak *ProduktoakLista = NULL;

    //int kantProduktoak = cargarProductosUsuario(&ProduktoakLista);


    int kantProduktoak = BueltatuListaProduktuak(&ProduktoakLista);

    if (kantProduktoak <= 0) {
    datos->kopurua = 0;
    datos->kategoriak = NULL;
    return; // Ez dago ezer kargatzeko
    }

    
    datos->kopurua = kantProduktoak;

    datos->kategoriak = (Kategoria *)malloc(kantProduktoak * sizeof(Kategoria));

    // Es buena práctica comprobar si malloc ha fallado
    if (datos->kategoriak == NULL) {
        printf("Error: No se ha podido reservar memoria para kategoriak\n");
        return; 
    }
    // printf("Produktoaren izena: %s\n", produktoa.nombre);

    for (int i = 0; i < datos->kopurua; i++)
    {
        // datos->kategoriak[i].id = i;
        datos->kategoriak[i].id = ProduktoakLista[i].id;
        printf("%d\n", datos->kategoriak[i].id);
        // sprintf(datos->kategoriak[i].izena, "Prod %d", i + 1);
        sprintf(datos->kategoriak[i].izena, "%s",
                ProduktoakLista[i].nombre); // VOY A TENER Q CAMBIAR ESTO PQ SI EL NOMBRE TIENE ESPACIOS PUEDE FALLAR
        datos->kategoriak[i].kantitatea = 0;
        datos->kategoriak[i].kopuruTotala = ProduktoakLista[i].cantidad;

        // datos->kategoriak[i].prezioa = 10.0 + (i * 5.0);
        datos->kategoriak[i].prezioa = atof(ProduktoakLista[i].precio);
        datos->kategoriak[i].aukeratuta = 0;
    }

    // 4. MUY IMPORTANTE: Liberar la lista auxiliar que ya no necesitamos
    free(ProduktoakLista);
}

APP_EGOERA inicioLogika(InicioDatos *datos, int ebentua, DatosProducto *datosProducto)
{
    if (ebentua == GERTAERA_IRTEN)
    {
        return PANT_IRTEN;
    }

    Uint32 orain = SDL_GetTicks();

    // Kalkulatu eduki osoaren altuera scroll-erako
    int rows = (datos->kopurua + COLUMNS - 1) / COLUMNS;
    int totalHeight = GRID_Y + rows * (BOX_SIZE + GAP);
    int viewHeight = 480;
    int maxScroll = totalHeight - viewHeight;
    if (maxScroll < 0)
    {
        maxScroll = 0;
    }

    // TEKLATUA: IDAZKETA ETA SCROLL
    if (datos->idazten)
    {
        int len = strlen(datos->bilaketa);
        if (ebentua == 8)
        { // Backspace (Ezabatu)
            if (len > 0)
            {
                datos->bilaketa[len - 1] = '\0';
            }
        }
        else if (ebentua >= 32 && ebentua <= 126)
        { // Letrak eta zenbakiak
            if (len < 40)
            { // Limitea
                char c = (char)ebentua;
                strncat(datos->bilaketa, &c, 1);
            }
        }
    }
    else
    {
        // Geziak teklatuarekin
        if (ebentua == TECLA_DOWN)
        {
            datos->inicioScroll += 20;
            if (datos->inicioScroll > maxScroll)
            {
                datos->inicioScroll = maxScroll;
            }
        }
        if (ebentua == TECLA_UP)
        {
            datos->inicioScroll -= 20;
            if (datos->inicioScroll < 0)
            {
                datos->inicioScroll = 0;
            }
        }
    }

    // --- KLIKAK KUDEAKETA ---
    if (ebentua == SAGU_BOTOIA_EZKERRA)
    {
        POSIZIOA p = saguarenPosizioa();

        // 1. SCROLL BARRAREN KONTROLA (Eskuinean: X > 610)
        // GRID_Y (130) hasita behera arte (480)
        if (p.x > 610 && p.x < 635 && p.y > 100 && p.y < 470)
        {
            // Barraren altuera totala: 370px (470-100)
            int barHeight = 370;
            int relativeY = p.y - 100;

            // Portzentajea kalkulatu
            float percentage = (float)relativeY / barHeight;

            // Scroll berria ezarri
            datos->inicioScroll = (int)(percentage * maxScroll);
            if (datos->inicioScroll < 0)
            {
                datos->inicioScroll = 0;
            }
            if (datos->inicioScroll > maxScroll)
            {
                datos->inicioScroll = maxScroll;
            }
        }

        // 2. SASKIAREN IKONOA (Berdea) - Joan Saski Pantailara
        // Koordenatuak gutxi gorabehera: X[540-600], Y[10-60]
        else if (p.x > 540 && p.x < 590 && p.y > 10 && p.y < 65)
        {
            datos->idazten = 0; // Idazteari utzi
            return PANTAILA_SASKIA;
        }

        //Produktoa gehitzeko ikonoa
        else if (p.x > 595 && p.x < 675 && p.y > 10 && p.y < 65)
        {
            datos->idazten = 0; // Idazteari utzi

            return PANTAILA_PRODUKTUA;
        }

        // 3. BILAKETA BARRA (Gorria) - Hasi idazten
        // Koordenatuak: X[10-530], Y[10-65]
        else if (p.x > 10 && p.x < 530 && p.y > 10 && p.y < 65)
        {
            datos->idazten = 1; // Idazten hasi
        }
        else
        {
            datos->idazten = 0; // Kanpoan klik egitean, idazteari utzi
        }

        // 4. GRID-A (Produktuak)
        // Scroll barra eremuan ez badago bakarrik
        /*
        for (int i = 0; i < datos->kopurua; i++)
        {
            int col = i % COLUMNS;
            int row = i / COLUMNS;
            int x = GRID_X + col * (BOX_SIZE + GAP);
            int y = GRID_Y + row * (BOX_SIZE + GAP);

            if (p.x > x && p.x < x + BOX_SIZE && p.y > y && p.y < y + BOX_SIZE)
            {
                // ... (Aurreko logika bera mantendu dugu) ...
                if (datos->trantsizioaZain == 1 && datos->klikatutakoId == i &&
                    (orain - datos->azkenKlikOrdua < KLIK_TARTEA))
                {
                    datos->trantsizioaZain = 0;
                    datos->klikatutakoId = -1;
                    return PANTAILA_PRODUKTUA;
                }
                else
                {
                    datos->klikatutakoId = i;
                    datos->azkenKlikOrdua = orain;
                    datos->trantsizioaZain = 1;
                }
            }
        }*/
        if (p.x < 610)
        {
            for (int i = 0; i < datos->kopurua; i++)
            {
                int col = i % COLUMNS;
                int row = i / COLUMNS;
                int x = GRID_X + col * (BOX_SIZE + GAP);

                // Kalkulatu Y erreala (SCROLL-AREKIN)
                int yReal = GRID_Y + row * (BOX_SIZE + GAP) - datos->inicioScroll;

                // Bakarrik pantaila barruan (eta goiburuaren azpian) badaude klikatu
                if (yReal > 70 && yReal < 480)
                {
                    if (p.x > x && p.x < x + BOX_SIZE && p.y > yReal && p.y < yReal + BOX_SIZE)
                    {
                        if (datos->trantsizioaZain == 1 && datos->klikatutakoId == i &&
                            (orain - datos->azkenKlikOrdua < KLIK_TARTEA))
                        {
                            datos->trantsizioaZain = 0;

                            datosProducto->modo = MODO_VISUALIZAR;
                            datosProducto->id = datos->kategoriak[i].id;
                            strcpy(datosProducto->nombre, datos->kategoriak[i].izena);
                            datosProducto->cantidad = datos->kategoriak[i].kopuruTotala;
                            datosProducto->precio = datos->kategoriak[i].prezioa;
                            

                            return PANTAILA_PRODUKTUA;
                        }
                        else
                        {
                            datos->klikatutakoId = i;
                            datos->azkenKlikOrdua = orain;
                            datos->trantsizioaZain = 1;
                        }
                    }
                }
            }
        }
    }

    // Timerra (klik bakarra baieztatzeko)
    if (datos->trantsizioaZain == 1)
    {
        if (orain > (datos->azkenKlikOrdua + KLIK_TARTEA))
        {
            int id = datos->klikatutakoId;
            if (id >= 0 && id < datos->kopurua)
            {
                datos->kategoriak[id].kantitatea++;
                datos->saskiaKop++;
            }
            datos->trantsizioaZain = 0;
            datos->klikatutakoId = -1;
        }
    }

    return PANTAILA_INICIO;
}

// --- MARRAZKETA ---
void marraztuMenuIkonoa(int x, int y)
{
    arkatzKoloreaEzarri(0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
        zirkuluaMarraztu(x, y + i * 7, 2);
        zuzenaMarraztu(x + 5, y + i * 7, x + 25, y + i * 7);
    }
}
void marraztuSaskiIkonoa(int x, int y)
{
    arkatzKoloreaEzarri(160, 180, 255);
    zirkuluaMarraztu(x, y, 20);
    arkatzKoloreaEzarri(255, 255, 255);
    zuzenaMarraztu(x - 10, y - 5, x + 10, y - 5);
    zuzenaMarraztu(x - 8, y - 5, x - 5, y + 5);
    zuzenaMarraztu(x + 8, y - 5, x + 5, y + 5);
    zuzenaMarraztu(x - 5, y + 5, x + 5, y + 5);
}

/*Produktu bat gehitu*/

void marraztuProduktuaGehitu(int x, int y)
{
    arkatzKoloreaEzarri(160, 180, 255);
    zirkuluaMarraztu(x, y, 20);
    arkatzKoloreaEzarri(255, 255, 255);
    zuzenaMarraztu(x, y - 7, x, y + 7);
    zuzenaMarraztu(x - 7, y, x + 7, y);
}

// BERRIA: Scroll Barra marrazteko funtzioa
void marraztuScrollBat(int x, int y, int h, int totalHeight, int currentScroll, int viewHeight)
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

// --- MARRAZKETA NAGUSIA ---

void inicioMarraztu(InicioDatos *datos)
{
    /*
    arkatzKoloreaEzarri(255, 255, 255);
    pantailaGarbitu();
    marraztuBotoiBeteaLogin(0, 0, 640, 480);

    // Goiburua (Urdina)
    arkatzKoloreaEzarri(150, 160, 255);
    marraztuLaukizuzenBiribila(10, 10, 620, 55, 10);

    // --- TESTUA EDO BILAKETA ---
    arkatzKoloreaEzarri(0, 0, 0);
    if (datos->idazten == 1 || strlen(datos->bilaketa) > 0)
    {
        // Idazten ari bada, hori erakutsi
        char temp[60];
        sprintf(temp, "%s%s", datos->bilaketa, datos->idazten ? "|" : ""); // Kurtsorea gehitu
        textuaIdatzi(30, 28, temp);
    }
    else
    {
        // Bestela titulu originala
        textuaIdatzi(30, 28, "Bilatu");
        textuaIdatzi(31, 28, "Bilatu");
    }

    int iconCenterY = 37;
    marraztuMenuIkonoa(500, iconCenterY - 7);
    marraztuSaskiIkonoa(560, iconCenterY);

    marraztuProduktuaGehitu(605, iconCenterY);


    if (datos->saskiaKop > 0)
    {
        arkatzKoloreaEzarri(255, 0, 0);
        zirkuluaMarraztu(575, iconCenterY - 15, 8);
        arkatzKoloreaEzarri(255, 255, 255);
        char num[5];
        sprintf(num, "%d", datos->saskiaKop);
        textuaIdatziTxikia(572, iconCenterY - 22, num);
    }

    // Grid marrazketa (lehen bezala)
    for (int i = 0; i < datos->kopurua; i++)
    {
        int col = i % COLUMNS;
        int row = i / COLUMNS;
        int x = GRID_X + col * (BOX_SIZE + GAP);
        int y = GRID_Y + row * (BOX_SIZE + GAP);

        arkatzKoloreaEzarri(230, 230, 230);
        marraztuLaukizuzenBiribila(x, y, BOX_SIZE, BOX_SIZE, 25);

        if (datos->kategoriak[i].kantitatea > 0)
        {
            arkatzKoloreaEzarri(255, 0, 0);
            int notifX = x + BOX_SIZE - 20;
            int notifY = y + 20;
            zirkuluaMarraztu(notifX, notifY, 15);
            arkatzKoloreaEzarri(255, 255, 255);
            char kantStr[5];
            sprintf(kantStr, "%d", datos->kategoriak[i].kantitatea);
            int testuX = (datos->kategoriak[i].kantitatea < 10) ? notifX - 3 : notifX - 7;
            textuaIdatzi(testuX, notifY - 8, kantStr);
        }
    }*/

    arkatzKoloreaEzarri(255, 255, 255);
    pantailaGarbitu();

    // 1. GRID-A MARRAZTU
    for (int i = 0; i < datos->kopurua; i++)
    {
        int col = i % COLUMNS;
        int row = i / COLUMNS;
        int x = GRID_X + col * (BOX_SIZE + GAP);
        int y = GRID_Y + row * (BOX_SIZE + GAP) - datos->inicioScroll;

        if (y > -150 && y < 480)
        {
            arkatzKoloreaEzarri(230, 230, 230);
            marraztuLaukizuzenBiribila(x, y, BOX_SIZE, BOX_SIZE, 25);

            arkatzKoloreaEzarri(0, 0, 0);
            textuaIdatzi(x + 20, y + 20, datos->kategoriak[i].izena);

            char prezioStr[20];
            sprintf(prezioStr, "%.2f E", datos->kategoriak[i].prezioa);
            textuaIdatziTxikia(x + 20, y + 50, prezioStr);

            if (datos->kategoriak[i].kantitatea > 0)
            {
                arkatzKoloreaEzarri(255, 0, 0);
                int notifX = x + BOX_SIZE - 20;
                int notifY = y + 20;
                zirkuluaMarraztu(notifX, notifY, 15);
                arkatzKoloreaEzarri(255, 255, 255);
                char kantStr[5];
                sprintf(kantStr, "%d", datos->kategoriak[i].kantitatea);
                int testuX = (datos->kategoriak[i].kantitatea < 10) ? notifX - 3 : notifX - 7;
                textuaIdatzi(testuX, notifY - 8, kantStr);
            }
        }
    }

    // 2. MASKARA ZURIA (Goian)
    arkatzKoloreaEzarri(255, 255, 255);
    marraztuBotoiBeteaLogin(0, 0, 640, 75);

    // 3. GOIBURUA
    arkatzKoloreaEzarri(150, 160, 255);
    marraztuLaukizuzenBiribila(10, 10, 620, 55, 10);

    // 4. TESTUA / BILAKETA
    arkatzKoloreaEzarri(0, 0, 0);
    if (datos->idazten == 1 || strlen(datos->bilaketa) > 0)
    {
        char temp[60];
        sprintf(temp, "%s%s", datos->bilaketa, datos->idazten ? "|" : "");
        textuaIdatzi(30, 28, temp);
    }
    else
    {
        textuaIdatzi(30, 28, "Bilatu");
        textuaIdatzi(31, 28, "Bilatu");
    }

    // 5. SCROLL BARRA (Eskuinean)
    // Edukiaren altuera totala kalkulatu berriro marrazketarako
    int rows = (datos->kopurua + COLUMNS - 1) / COLUMNS;
    int totalHeight = GRID_Y + rows * (BOX_SIZE + GAP);
    // Barra posizioa: X=615, Y=100, Altuera=370, View=480
    marraztuScrollBat(615, 100, 370, totalHeight, datos->inicioScroll, 480);

    // 6. IKONOAK
    int iconCenterY = 37;
    marraztuMenuIkonoa(500, iconCenterY - 7);
    marraztuSaskiIkonoa(560, iconCenterY);
    marraztuProduktuaGehitu(605, iconCenterY);

    if (datos->saskiaKop > 0)
    {
        arkatzKoloreaEzarri(255, 0, 0);
        zirkuluaMarraztu(575, iconCenterY - 15, 8);
        arkatzKoloreaEzarri(255, 255, 255);
        char num[5];
        sprintf(num, "%d", datos->saskiaKop);
        textuaIdatziTxikia(572, iconCenterY - 22, num);
    }
}