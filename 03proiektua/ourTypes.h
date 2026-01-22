#ifndef OURTYPES_H
#define OURTYPES_H

#include <SDL.h>

typedef enum
{
    PANTAILA_LOGIN,
    PANTAILA_ERREGISTROA,
    PANTAILA_SEKTOREAK,
    PANTAILA_INICIO,
    PANTAILA_PRODUKTUA,
    PANTAILA_SASKIA, 
    PANTAILA_JOKOA,
    PANT_IRTEN
} APP_EGOERA;

typedef enum {
    MODO_CREAR,
    MODO_VISUALIZAR
} PRODUCTO_MODO;

typedef struct
{
    char erabiltzailea[32];
    char pasahitza[32];
    char pasahitzaIzk[32];
    int fokua;
} LoginDatos;

// Datuen egitura (Ordena garrantzitsua da main.c-ko hasieraketarako)
typedef struct
{
    char enpresaIzena[50];
    char nif[20];
    char postaKodea[10];
    char emaila[50];
    char erabiltzailea[32];
    char pasahitza[32];
    char pasahitzaIzk[32];
    int fokua; // Fokua amaieran
} ErregistroDatos;

typedef struct 
{
    int id;
    char nombre[40];
   // float precio;
    char precio[5];
    char descripcion[250];
    //int cantidad;
    char cantidad[4];
    //int idEmpresa;
    char idEmpresa[4];
    int fokua;

    int inicioScroll;

    int sectores[10];
    int numSectores;

} Produktuak;

typedef struct 
{
    int id;
    char nombre[40];
    float precio;
    char descripcion[250];
    int cantidad;
    int idEmpresa;
    
    PRODUCTO_MODO modo;

} DatosProducto;

// --- SEKTOREAK DATUAK ---
typedef struct
{
    int aukeratuak[9];      // 0 = Ez, 1 = Bai
    char erabiltzailea[50]; // Erabiltzailearen izena gordetzeko
} SektoreakDatos;


typedef struct
{
    int id;
    char enpresaIzena[50];
    char nif[20];
    char postaKodea[10];
    char emaila[50];
    char erabiltzailea[32];
    char pasahitza[32];
    int sektoreak[9];
} Erabiltzailea;

typedef struct
{
    int id;
    char izena[50];
    int kantitatea;
    float prezioa;
    int aukeratuta; // 1 = Bai, 0 = Ez
    int kopuruTotala;

} Kategoria; //SARTUTAKO PRODUKTOAK 
/*CREO Q LUEGO LO MEJOR VA A SER UTILIZAR EL DE PRODUKTOAK PARA TENER DIFERENTES*/

typedef struct
{
    // Kategoria kategoriak[9];
    Kategoria *kategoriak; //LA LISTA DE PRODUCTOS Q SE MUESTRAN
    int kopurua;
    int saskiaKop;

    // Klik kontrola
    int klikatutakoId;
    Uint32 azkenKlikOrdua;
    int trantsizioaZain;

    // --- ARRASTRATZEKO ALDAGIAK (Drag & Drop) ---
    int arrastratzen;       // 0 = Ez, 1 = Bai (Mugitzen ari da)
    int arrastratuPosiblea; // 1 = Klik (LCTRL) sakatuta, baina oraindik ez da mugitu
    int arrastratutakoId;   // Zein produktu ari den mugitzen
    int klikHasieraX;       // Hasierako posizioa distantzia kalkulatzeko
    int klikHasieraY;

    // --- BILAKETA ETA IDAZKETA (BERRIAK) ---
    char bilaketa[50]; // Idazten duzun testua
    int idazten;       // 1 = Idazten ari da, 0 = Ez

    // --- SCROLL ALDAGIAK ---
    int saskiaScroll;
    int inicioScroll;

    //Produktua
    int aukertatutakoProduktua;

} InicioDatos;


typedef struct
{
    int id;
    char sektorea[50];
} Sektoreak;

//Encriptatzeko:

typedef unsigned long long hash_t;



#endif

