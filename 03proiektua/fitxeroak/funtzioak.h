#ifndef FUNTZIOAKFITXEROAK_h
#define FUNTZIOAKFITXEROAK_h

#include "../ourTypes.h"

//enpresa
/*
//int EnpresaGehitu(ErregistroDatos enpresa);
int EnpresaGehitu(ErregistroDatos enpresa, SektoreakDatos datos);
Erabiltzailea bilatuErabiltzaileaById(int id);
int login(LoginDatos login);
int ErabiltzaileaIzenHorrekinBilatu(ErregistroDatos enpresaBerria);


Produktuak BueltatuProduktuak();
//int gehituProduktuak(Produktuak Produktuak);
int BueltatuListaProduktuak(Produktuak **lista);
//int BueltatuListaProduktuakSektoreka(Produktuak **lista, int sectoresVips[], int nVips);

int gehituProduktuak(Produktuak Produktuak, SektoreakDatos datos);


void limpiarNuevaLinea(char *str);
int buscarultimoID(char ruta[150]);

hash_t generar_hash(const char *pasahitza, const char *salt);
*/

// Enpresa funtzioak
int EnpresaGehitu(ErregistroDatos enpresa, SektoreakDatos datos);
Erabiltzailea bilatuErabiltzaileaById(int id);
int login(LoginDatos login);
int ErabiltzaileaIzenHorrekinBilatu(ErregistroDatos enpresaBerria);

// Produktu funtzioak
Produktuak BueltatuProduktuak();
int BueltatuListaProduktuak(Produktuak **lista);
int gehituProduktuak(Produktuak Produktuak, SektoreakDatos datos);
Produktuak BueltatuProduktuaById(int id);


// Laguntza funtzioak
void limpiarNuevaLinea(char *str);
int buscarultimoID(char ruta[150]);
hash_t generar_hash(const char *pasahitza, const char *salt);
void GarbituProduktua(Produktuak *p);



//erosketak
int erosketaGorde(int idErosle, InicioDatos datos);
int erosketaXehetasunaGorde(int idErosketa, int idProduktoa, int kantitatea, float prezioa);


#endif