#ifndef EBENTUAK_H
#define EBENTUAK_H
#include <SDL.h>

typedef struct S_POSIZIOA
{
    int x;
    int y;
} POSIZIOA;

/*
  Helburua: Funztio hau tekla bat sakatu arte zain dago,
  eta ondoren zenbaki oso baten bitartez zein sakatu den adieraziko digu.
  Sarrera:
  Irteera: Sakatuta teklaren identifikadorea
*/
int ebentuaJasoGertatuBada(void);
POSIZIOA saguarenPosizioa();

// --- SAGU BIRTUALA ---
void saguBirtualaKudeatu(void);


char *devolverTextoIntroducido(); //devolver la posición de textEvento q es la variable donde guardamos el texto metido por el usuario

// Abiadura (pixeletan)
#define SAGU_ABIADURA 5
#define VELOCIDAD_ANIM 1

#define TECLA_ENTER 13
#define NUM_FRAMES 48 //numero de irudis
//#define VELOCIDAD_ANIM 0 //la velocidad maxima q puede ir el ordenador
/*
#define SAGU_BOTOIA_ERDIKOA 2
#define SAGU_MUGIMENDUA 4
#define SAGU_BOTOIA_ESKUINA 5
#define SAGU_BOTOIA_EZKERRA 6
#define GERTAERA_IRTEN 12
 */

#define SAGU_BOTOIA_EZKERRA 1
#define SAGU_BOTOIA_ERDIKOA 2
#define SAGU_BOTOIA_ESKUINA 3
#define SAGU_MUGIMENDUA 4
#define GERTAERA_IRTEN 12


#define TECLA_RETURN 13
#define TECLA_ESCAPE 27
#define TECLA_SPACE 32
#define TECLA_0 48
#define TECLA_1 49
#define TECLA_2 50
#define TECLA_3 51
#define TECLA_4 52
#define TECLA_5 53
#define TECLA_6 54
#define TECLA_7 55
#define TECLA_8 56
#define TECLA_9 57
#define TECLA_a 97
#define TECLA_b 98
#define TECLA_c 99
#define TECLA_d 100
#define TECLA_e 101
#define TECLA_f 102
#define TECLA_g 103
#define TECLA_h 104
#define TECLA_i 105
#define TECLA_j 106
#define TECLA_k 107
#define TECLA_l 108
#define TECLA_m 109
#define TECLA_n 110
#define TECLA_o 111
#define TECLA_p 112
#define TECLA_q 113
#define TECLA_r 114
#define TECLA_s 115
#define TECLA_t 116
#define TECLA_u 117
#define TECLA_v 118
#define TECLA_w 119
#define TECLA_x 120
#define TECLA_y 121
#define TECLA_z 122
#define TECLA_UP 273
#define TECLA_DOWN 274
#define TECLA_RIGHT 275
#define TECLA_LEFT 276

#define EBENTU_TESTU_SARRERA 1001

#endif
