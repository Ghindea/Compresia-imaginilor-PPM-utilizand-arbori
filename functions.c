#include "header.h"
double sqr(double x) {
    return x*x;
}

double average(RGB **grid, unsigned int x, unsigned int y, unsigned int size) {
    double red = 0, green = 0, blue = 0, mean = 0;

    for (int i = x; i < x+size; i++) {
        for (int j = y; j < y+size; j++) {
            red     += grid[i][j].red;
            green   += grid[i][j].green;
            blue    += grid[i][j].blue;
        }
    }

    red     /= sqr(size);
    green   /= sqr(size);
    blue    /= sqr(size);

    for (int i = x; i < x+size; i++) {
        for (int j = y; j < y+size; j++) {
            mean += (sqr(red-grid[i][j].red) + sqr(green-grid[i][j].green) + sqr(blue-grid[i][j].blue));
        }
    }
    mean    /= (3 * sqr(size));
    return mean;
}

void show(TArb arb) {
    if (arb->type) {
        printf("%d-%d-%d ", arb->data.red, arb->data.green, arb->data.blue);
    } else {
        printf("0\n");
        show(arb->sts);
        show(arb->drs);
        show(arb->stj);
        show(arb->drj);
    }

}
RGB ** readData(unsigned int *size, FILE *in) {
    int light = 0;
    char *type = malloc(4*sizeof(char));
    fread(type, sizeof(char), 3, in);
    fscanf(in, "%d", size);
    fscanf(in, "%d", size);
    fscanf(in, "%d", &light);
    fread(type, sizeof(char), 1, in);

    // //RGB (*grid)[*size] = malloc(sizeof(RGB[*size][*size]));
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
TArb makeArb(RGB **grid, int x, int y, int size, int factor) {
    TArb arb = malloc(sizeof(TNod));
    if (average(grid, x, y, size) <= factor) {
        arb->type = 1;
        arb->data.red = grid[x][y].red;
        arb->data.green = grid[x][y].green;
        arb->data.blue = grid[x][y].blue;

        return arb;
    } else {
        arb->type = 0;
        arb->sts = makeArb(grid, x, y, size/2, factor);
        arb->drs = makeArb(grid, x, y + size/2, size/2, factor);
        arb->drj = makeArb(grid, x + size/2, y + size/2, size/2, factor);
        arb->stj = makeArb(grid, x + size/2, y, size/2, factor);
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
    TLista tmp = (*L).inc;
    L->inc = L->inc->urm;
    free(tmp);
}
