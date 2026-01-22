#ifndef INICIO_H
#define INICIO_H

#include "../../ourTypes.h"


void inicioDatuakHasieratu(InicioDatos *datos);
//APP_EGOERA inicioLogika(InicioDatos *datos, int ebentua);
APP_EGOERA inicioLogika(InicioDatos *datos, int ebentua, DatosProducto *datosProducto);

void inicioMarraztu(InicioDatos *datos);

int cargarProductosUsuario(Produktuak **miLista);

#endif