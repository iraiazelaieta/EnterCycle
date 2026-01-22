#ifndef PRODUKTOAK_H
#define PRODUKTOAK_H

#include "../../ourTypes.h"
#include "ebentoak.h"

//APP_EGOERA ProduktuaGehitu(int logoId, Produktuak *produktuakGehitu, int ebentua);
APP_EGOERA ProduktuaGehitu(int logoId, Produktuak *produktuakGehitu, int ebentua, DatosProducto *datosProducto);

//void marraztuHorria(int logoId, Produktuak *produktuakGehitu);
void marraztuHorria(int logoId, Produktuak *produktuakGehitu, DatosProducto *datosProducto);
//void marraztuScrollBat(int x, int y, int h, int totalHeight, int currentScroll, int viewHeight);


#endif