#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appState.h"
#include "funtzioak.h"

/*-------------------ENPRESAK------------------------*/

int EnpresaGehitu(ErregistroDatos enpresa, SektoreakDatos datos)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/erregistroak.txt";
    int contadorId;

    char nire_salt[] = "PBL_1_Infor"; // Salt fijo bat
    hash_t pasahitza;

    pasahitza = generar_hash(enpresa.pasahitza, nire_salt);

    contadorId = buscarultimoID(ruta);

    pf = fopen(ruta, "a");

    if (pf == NULL)
    {
        printf("Errorea fitxategia irekitzean.\n");
        return -1;
    }

    fprintf(pf, "%d;%s;%s;%s;%s;%s;%llx;", contadorId, enpresa.nif, enpresa.enpresaIzena, enpresa.postaKodea,
            enpresa.emaila, enpresa.erabiltzailea, pasahitza);

    int lehena = 1; // Jakiteko lehengoa elementua den eta koma bat jartzeko edo ez

    // Guardar el array
    for (int i = 0; i < 9; i++)
    {
        if (datos.aukeratuak[i] == 1)
        {
            if (!lehena)
            {
                fprintf(pf, ",");
            }

            fprintf(pf, "%d", i);
            lehena = 0;
        }
    }

    fprintf(pf, "\n");

    fclose(pf);

    return contadorId;
}

int ErabiltzaileaIzenHorrekinBilatu(ErregistroDatos enpresaBerria)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/erregistroak.txt";

    int encontrado = 0;
    int id;

    pf = fopen(ruta, "r");

    if (pf == NULL)
    {
        printf("Error al abrir el fichero");
        return -1;
    }

    ErregistroDatos enpresa;

    // preguntar lo que buscan
    char linea[512];
    fgets(linea, sizeof(linea), pf); // saltar cabecera

    while (fgets(linea, sizeof(linea), pf) && !encontrado)
    {
        if (sscanf(linea, "%d;%19[^;];%49[^;];%9[^;];%49[^;];%49[^;];%49[^;]", &id, enpresa.nif, enpresa.enpresaIzena,
                   enpresa.postaKodea, enpresa.emaila, enpresa.erabiltzailea, enpresa.pasahitza) == 7)
        {

            if (strcmp(enpresa.erabiltzailea, enpresaBerria.erabiltzailea) == 0)
            {
                encontrado = 1;
            }
        }
    }

    fclose(pf);

    return encontrado;
}

int login(LoginDatos login)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/erregistroak.txt";

    int encontrado = 0;
    int id;

    char nire_salt[] = "PBL_1_Infor"; // Salt fijo bat
    hash_t pasahitza;
    hash_t BenetakoPasahitza;

    pf = fopen(ruta, "r");

    if (pf == NULL)
    {
        printf("Error al crear el fichero");
        return -2;
    }

    ErregistroDatos enpresa;

    // preguntar lo que buscan
    char linea[512];
    fgets(linea, sizeof(linea), pf); // saltar cabecera

    // printf("'%s' (%lu)\n", login.pasahitza, strlen(login.pasahitza));

    while (fgets(linea, sizeof(linea), pf) && !encontrado)
    {
        if (sscanf(linea, "%d;%19[^;];%49[^;];%9[^;];%49[^;];%49[^;];%llx", &id, enpresa.nif, enpresa.enpresaIzena,
                   enpresa.postaKodea, enpresa.emaila, enpresa.erabiltzailea, &BenetakoPasahitza) == 7)
        {

            //  printf("'%s' (%lu)\n", enpresa.pasahitza, strlen(enpresa.pasahitza));

            //   limpiarNuevaLinea(enpresa.pasahitza);
            //  limpiarNuevaLinea(login.pasahitza);

            // encriptar la contraseña q nos han metido
            pasahitza = generar_hash(login.pasahitza, nire_salt);

            if (pasahitza == BenetakoPasahitza && strcmp(login.erabiltzailea, enpresa.erabiltzailea) == 0)
            {
                encontrado = 1;
            }
        }
    }

    if (!encontrado)
    {
        id = -1;
    }

    fclose(pf);

    return id;
}

Erabiltzailea bilatuErabiltzaileaById(int id)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/erregistroak.txt";

    Erabiltzailea enpresa;
    int encontrado = 0;
    char linea[512];

    pf = fopen(ruta, "r"); // abrimos el fichero

    if (pf == NULL)
    {
        printf("Error al crear el fichero");
        enpresa.id = -1;
        return enpresa;
    }

    fgets(linea, sizeof(linea), pf); // saltar cabecera

    while (fgets(linea, sizeof(linea), pf) && !encontrado)
    {
        char sectoresAux[20] = ""; // Para guardar temporalmente la cadena "5,6,7,8,9"

        if (sscanf(linea, "%d;%19[^;];%49[^;];%9[^;];%49[^;];%49[^;];%49[^;];%19[^\n]", &enpresa.id, enpresa.nif,
                   enpresa.enpresaIzena, enpresa.postaKodea, enpresa.emaila, enpresa.erabiltzailea, enpresa.pasahitza,
                   sectoresAux) >= 8)
        {

            if (enpresa.id == id)
            {

                int s = 0;

                if (strlen(sectoresAux) > 0)
                {
                    char *token = strtok(sectoresAux, ",");
                    while (token != NULL && s < 10)
                    {
                        enpresa.sektoreak[s] = atoi(token);
                        s++;
                        token = strtok(NULL, ",");
                    }
                }

                encontrado = 1;
            }
        }
    }

    if (!encontrado)
    {
        enpresa.id = 0;
    }

    fclose(pf);

    return enpresa;
}

/*-------------------PRODUKTUAK------------------------*/

int gehituProduktuak(Produktuak Produktuak, SektoreakDatos datos)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/produktuak.txt";
    int contadorId = 1;

    contadorId = buscarultimoID(ruta);

    pf = fopen(ruta, "a");

    if (pf == NULL)
    {
        printf("Errorea fitxategia irekitzean.\n");
        return 1;
    }

    fprintf(pf, "%d;%s;%s;%s;%s;%s;", contadorId, Produktuak.nombre, Produktuak.precio, Produktuak.descripcion,
            Produktuak.cantidad, Produktuak.idEmpresa);

    int lehena = 1; // Jakiteko lehengoa elementua den eta koma bat jartzeko edo ez

    // Guardar el array
    for (int i = 0; i < 9; i++)
    {
        if (datos.aukeratuak[i] == 1)
        {
            if (!lehena)
            {
                fprintf(pf, ",");
            }

            fprintf(pf, "%d", i);
            lehena = 0;
        }
    }

    fprintf(pf, "\n");

    fclose(pf);

    return 0;
}

// probar si se puede hacer con array dinamico (por ahora devolvemos uno)

// Produktuak BueltatuProduktuak(int produktoKopurua)
Produktuak BueltatuProduktuaById(int id)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/produktuak.txt";
    char linea[512];
    // int id;
    int encontrado = 0;

    // Produktuak* ProduktoLista = (Produktuak*)malloc(produktoKopurua * sizeof(Produktuak));

    Produktuak produktoa;

    // Inicializamos la estructura para evitar basura en la memoria
    memset(&produktoa, 0, sizeof(Produktuak));

    pf = fopen(ruta, "r");

    if (pf == NULL)
    {
        printf("Errorea fitxategia irekitzean.\n");

        produktoa.fokua = -1;

        return produktoa;
    }

    fgets(linea, sizeof(linea), pf); // saltar cabecera

    while (fgets(linea, sizeof(linea), pf) && !encontrado)
    {
        char sectoresAux[20] = ""; // Para guardar temporalmente la cadena "5,6,7,8,9"

        if (sscanf(linea, "%d;%49[^;];%19[^;];%99[^;];%9[^;];", &produktoa.id, produktoa.nombre, produktoa.precio,
                   produktoa.descripcion, produktoa.cantidad) >= 5)
        {

            if (produktoa.id == id)
            {
                encontrado = 1;
            }
        }
    }

    if (!encontrado)
    {
        produktoa.id = 0;
    }

    fclose(pf);

    return produktoa;
}

// int BueltatuListaProduktuak(Produktuak **lista, int *sectoresFiltro, int nFiltro)
int BueltatuListaProduktuak(Produktuak **lista)
{

    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/produktuak.txt";
    char linea[512];
    int id;

    int capacidad = 10;
    int usados = 0;

    // Produktuak* ProduktoLista = (Produktuak*)malloc(produktoKopurua * sizeof(Produktuak))

    pf = fopen(ruta, "r");

    if (pf == NULL)
    {
        printf("Errorea fitxategia irekitzean.\n");

        return -1;
    }

    *lista = malloc(capacidad * sizeof(Produktuak));

    if (!*lista)
    {
        return -1;
    }

    fgets(linea, sizeof(linea), pf); // saltar la cabecera

    while (fgets(linea, sizeof(linea), pf))
    {
        if (usados == capacidad)
        {
            capacidad *= 2;

            *lista = realloc(*lista, capacidad * sizeof(Produktuak));

            if (!*lista)
            {
                return -1;
            }
        }

        char sectoresAux[20] = ""; // Para guardar temporalmente la cadena "5,6,7,8,9"

        int irakurrita = sscanf(linea,

                                "%d;%49[^;];%19[^;];%99[^;];%9[^;];%9[^;];%20[^\n]",

                                &(*lista)[usados].id,

                                (*lista)[usados].nombre,

                                (*lista)[usados].precio,

                                (*lista)[usados].descripcion,

                                (*lista)[usados].cantidad,

                                (*lista)[usados].idEmpresa,

                                sectoresAux);

        // 2. Si se han leído sectores, los procesamos

        (*lista)[usados].numSectores = 0;

        if (irakurrita == 7 && strlen(sectoresAux) > 0)

        {

            char *token = strtok(sectoresAux, ",");

            int s = 0;

            while (token != NULL && s < 10) // Evitar desbordar el array de sectores

            {

                (*lista)[usados].sectores[s] = atoi(token);

                s++;

                token = strtok(NULL, ",");
            }

            (*lista)[usados].numSectores = s;
        }

        usados++;
    }

    fclose(pf);

    return usados;
}
/*
int BueltatuListaProduktuakSektoreka(Produktuak **lista, int sectoresVips[], int nVips)
{
    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/produktuak.txt";
    char linea[512];
    int capacidad = 10;
    int usados = 0;

    pf = fopen(ruta, "r");
    if (pf == NULL) {
        printf("Errorea fitxategia irekitzean.\n");
        return -1;
    }

    *lista = malloc(capacidad * sizeof(Produktuak));
    if (!*lista) { fclose(pf); return -1; }

    fgets(linea, sizeof(linea), pf); // Goiburua jauzi

    while (fgets(linea, sizeof(linea), pf)) {
        Produktuak pTmp; // Datuak hemen kargatuko ditugu lehenik
        char sectoresAux[50] = ""; // Sektoreen katea (0,1,2...)

        // GARRANTZITSUA: sscanf-ek pTmp-ren helbideetan idatzi behar du
        int irakurrita = sscanf(linea,
            "%d;%49[^;];%19[^;];%99[^;];%9[^;];%9[^;];%49[^\n]",
            &pTmp.id,
            pTmp.nombre,
            pTmp.precio,
            pTmp.descripcion,
            pTmp.cantidad,
            pTmp.idEmpresa,
            sectoresAux);

        if (irakurrita >= 6) {
            // 1. Sektoreak prozesatu
            pTmp.numSectores = 0;
            if (strlen(sectoresAux) > 0) {
                char *token = strtok(sectoresAux, ",");
                while (token != NULL && pTmp.numSectores < 10) {
                    pTmp.sectores[pTmp.numSectores++] = atoi(token);
                    token = strtok(NULL, ",");
                }
            }

            // 2. Filtroa aplikatu: Erabiltzailearen sektoreekin bat datorren ikusi
            int coincide = 0;
            for (int i = 0; i < pTmp.numSectores; i++) {
                for (int j = 0; j < nVips; j++) {
                    if (pTmp.sectores[i] == sectoresVips[j]) {
                        coincide = 1;
                        break;
                    }
                }
                if (coincide) break;
            }

            // 3. Bat badator, zerrendara gehitu
            if (coincide) {
                if (usados == capacidad) {
                    capacidad *= 2;
                    Produktuak *temp = realloc(*lista, capacidad * sizeof(Produktuak));
                    if (temp == NULL) break; // Memoria errorea
                    *lista = temp;
                }
                (*lista)[usados] = pTmp; // Egitura osoa kopiatu
                usados++;
            }
        }
    }

    fclose(pf);
    return usados;
}
*/

/*-------------------EROSKETA---------------------*/

int erosketaGorde(int idErosle, InicioDatos datos)
{

    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/erosketak.txt";
    char linea[512];
    int id;
    int i;

    float prezioTotala = 0;

    // Lehenengo buelta: edukiaren tamaina osoa kalkulatu scroll barrarako
    for (int i = 0; i < datos.kopurua; i++)
    {
        if (datos.kategoriak[i].kantitatea > 0)
        {
            float lerroPrezioa = datos.kategoriak[i].prezioa * datos.kategoriak[i].kantitatea;

            if (datos.kategoriak[i].aukeratuta)
            {
                prezioTotala += lerroPrezioa;
            }
        }
    }

    id = buscarultimoID(ruta);

    pf = fopen(ruta, "a");

    if (pf == NULL)
    {
        printf("Errorea fitxategia irekitzean.\n");
        return 1;
    }

    fprintf(pf, "%d;%d;%f\n", id, idErosle, prezioTotala);

    fclose(pf);

    for (i = 0; i < datos.kopurua; i++)
    {
        if (datos.kategoriak[i].kantitatea > 0)
        {
            erosketaXehetasunaGorde(id, datos.kategoriak[i].id, datos.kategoriak[i].kantitatea,
                                    datos.kategoriak[i].prezioa);
        }
    }

    return 0;
}

int erosketaXehetasunaGorde(int idErosketa, int idProduktoa, int kantitatea, float prezioa)
{

    FILE *pf;
    char ruta[150] = "03proiektua/fitxeroak/erosketaXehetasunak.txt";
    char linea[512];
    int id;

    id = buscarultimoID(ruta);

    pf = fopen(ruta, "a");

    if (pf == NULL)
    {
        printf("Errorea fitxategia irekitzean.\n");
        return 1;
    }

    fprintf(pf, "%d;%d;%d;%f\n", idErosketa, idProduktoa, kantitatea, prezioa);

    fclose(pf);

    return 0;
}

/*-------------------Laguntza funtzioak------------------------*/

int buscarultimoID(char ruta[150])
{
    FILE *pf = fopen(ruta, "r");
    if (pf == NULL)
    {
        return 1;
    }

    char linea[512];
    int id = 0;
    while (fgets(linea, sizeof(linea), pf))
    {
        sscanf(linea, "%d;", &id);
    }
    fclose(pf);
    return id + 1;
}

void limpiarNuevaLinea(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

// encriptatzeko

// Salt --> bi pasahitza berdinak izatekotan, hash-a desberdina izateko
hash_t generar_hash(const char *pasahitza, const char *salt)
{
    // Valores iniciales arbitrarios (Primos grandes)
    //'0x' --> ez da zenbakiaren parte
    // ULL --> U (zenbaki positiboa adierazi) eta LL (longo long, 64 bits maximo)
    hash_t h = 0xcbf29ce484222325ULL;
    // kolisioa ez gertatzeko, bi pasahitza desberdin hash berdina ez izateko
    hash_t p = 0x100000001b3ULL;

    // 1. Mezclar el SALT primero
    for (int i = 0; salt[i] != '\0'; i++)
    {
        h = h ^ (hash_t)salt[i]; // Operación XOR
        h *= p;                  // Multiplicación por un primo
    }

    // 2. Mezclar la CONTRASEÑA
    // Pasahitza hash-arekin lotu
    for (int i = 0; pasahitza[i] != '\0'; i++)
    {
        h = h ^ (hash_t)pasahitza[i];
        h *= p;
    }

    return h;
}

void GarbituProduktua(Produktuak *p)
{
    if (p != NULL)
    {
        memset(p, 0, sizeof(Produktuak)); // Memoria guztia 0an jarri
        p->fokua = 0;                     // Fokua kendu
    } // Quita el foco de los inputs
}