#ifndef IMAGEN_H
#define IMAGEN_H

#define MAX_IMG 10

int irudiaKargatu(char *fileName);
void irudiakMarraztu(void);
void irudiaMugitu(int numImg, int x, int y);
void irudiaEskalatu(int numImg, int w, int h); // Tamaina aldatzeko
void irudiaKendu(int id);
void irudiaMarraztuId(int id, int x, int y);

#endif