#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned char red, green, blue;
} RGB;

typedef struct nod {
    unsigned char type;
    RGB data;
    struct nod *sts, *drs, *stj, *drj;
    /* st - stanga; dr - dreapta; s - sus; j - jos */
} TNod, *TArb;

typedef struct celula {
    TArb info;
    struct celula *urm;
} TCelula, *TLista;

typedef struct coada {
    TLista inc, sf;
}TCoada;

TArb makeArb(RGB **grid, int x, int y, int size, int factor);
RGB ** readData(unsigned int *size, FILE *in);

double average(RGB **grid, unsigned int x, unsigned int y, unsigned int size);
void show(TArb arb);

void * initQ();
void extrQ(TCoada *L);
void addCell(TCoada *L, TArb root);
void extrQ(TCoada *L);

void task1(RGB **grid, unsigned int size, unsigned int factor, FILE *out);
void task2(TArb arb, unsigned int *size, FILE *out);
void task3(FILE *in, FILE *out);