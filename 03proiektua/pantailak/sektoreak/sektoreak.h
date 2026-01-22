#ifndef SEKTOREAK_H
#define SEKTOREAK_H

#include "ourTypes.h" // <--- HAU BEHARREZKOA DA

//APP_EGOERA sektoreakLogika(SektoreakDatos *datos, int ebentua);
//APP_EGOERA sektoreakLogika(SektoreakDatos *datos, int ebentua, ErregistroDatos *regDat);
APP_EGOERA sektoreakLogika(SektoreakDatos *datos, int ebentua, ErregistroDatos *regDat, Produktuak *proDat, APP_EGOERA aurrekoEgoera);

void sektoreakMarraztu(SektoreakDatos *datos);

#endif