/* GHINDEA DANIEL-TEODOR 315CB */

#include "header.h"

long long average(RGB **grid, RGB *avg, unsigned int x, unsigned int y, unsigned int size) {
    int red = 0, green = 0, blue = 0;
    long long mean = 0;

    /* culoare medie pe canale de culori (RGB) */
    for (int i = x; i < x+size; i++) {
        for (int j = y; j < y+size; j++) {
            red     += grid[i][j].red;
            green   += grid[i][j].green;
            blue    += grid[i][j].blue;
        }
    }

    red     /= size * size;   avg->red    = red;
    green   /= size * size;   avg->green  = green;
    blue    /= size * size;   avg->blue   = blue;

    /* determinare mean */
    for (int i = x; i < x+size; i++) {
        for (int j = y; j < y+size; j++) {
            mean += (red-grid[i][j].red) * (red-grid[i][j].red);
            mean += (green-grid[i][j].green) * (green-grid[i][j].green);
            mean += (blue-grid[i][j].blue) * (blue-grid[i][j].blue);
        }
    }
    mean    /= (3 * size * size);
    return mean;
}

RGB ** readData(unsigned int *size, FILE *in) {         // citirea "imaginii" (in matrice)
    int light = 0;
    char *type = calloc(4, sizeof(char));
    fread(type, sizeof(char), 3, in);
    fscanf(in, "%d", size);
    fscanf(in, "%d", size);
    fscanf(in, "%d", &light);
    fread(type, sizeof(char), 1, in);

    RGB **grid = (RGB **)calloc(*size, sizeof(RGB *));
    for (int i = 0; i < *size; i++) {
        grid[i] = calloc(*size, sizeof(RGB));
    }

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fread(&grid[i][j].red, sizeof(char), 1, in);
            fread(&grid[i][j].green, sizeof(char), 1, in);
            fread(&grid[i][j].blue, sizeof(char), 1, in);
        }
    }
    free(type);

    return grid;
}
TArb makeArb(RGB **grid, int x, int y, int size, int factor) {  // construirea arborelui plecand de la matrice
    TArb arb = calloc(1, sizeof(TNod));
    RGB avg;
    if (average(grid, &avg, x, y, size) <= factor) {    // salvare date RGB in nod
        arb->type = 1;
        arb->data.red   = avg.red;
        arb->data.green = avg.green;
        arb->data.blue  = avg.blue;

        return arb;
    } else {    // parcurgere in sens trigonometric
        arb->type = 0;
        arb->sts = makeArb(grid, x, y, size/2, factor);             // cadranul II
        arb->drs = makeArb(grid, x, y + size/2, size/2, factor);    // cadranul I
        arb->drj = makeArb(grid, x + size/2, y + size/2, size/2, factor);   // cadranul IV
        arb->stj = makeArb(grid, x + size/2, y, size/2, factor);    // cadranul III
    }
    return arb;
}

void * initQ() {
    TCoada *L = (TCoada *) malloc(sizeof(TCoada));

    if (! L) return NULL;
    L->inc = L->sf = NULL;

    return L;
}
void addCell(TCoada *L, TArb root) {
    TLista fifo = (TLista) malloc(sizeof(TCelula));
    fifo->info = root; fifo->urm = NULL;

    if(L->sf) L->sf->urm = fifo;
        else L->inc = fifo;
    L->sf = fifo;
}
void extrQ(TCoada *L) {
    TLista tmp = L->inc;
    L->inc = L->inc->urm;
    free(tmp);
}

void cleanGrid(RGB **grid, int size) {
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

void cleanArb(TArb arb) {
    if (! arb) return;
    if (arb->sts) cleanArb(arb->sts);
    if (arb->drs) cleanArb(arb->drs);
    if (arb->drj) cleanArb(arb->drj);
    if (arb->stj) cleanArb(arb->stj);

    free(arb);
}

void cleanQ(TCoada *Q) {
    TLista tmp = Q->inc, aux;
    while(tmp) {
        aux = tmp;
        tmp = tmp->urm;
        free(aux);
    }
    free(Q);
    free(tmp);
}