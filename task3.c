#include "header.h"
TArb initArb() {
    TArb root = malloc(sizeof(TNod));
    root->drj = root->drs = root->stj = root->sts = NULL;
    
    return root;
}
void readNod(TArb *arb, FILE *in) {
    fread(&((*arb)->type), sizeof(unsigned char), 1, in);
    if ((*arb)->type) {
        fread(&((*arb)->data.red),  sizeof(unsigned char), 1, in);
        fread(&((*arb)->data.green), sizeof(unsigned char), 1, in);
        fread(&((*arb)->data.blue), sizeof(unsigned char), 1, in);
    }
}
void makeMatrix(RGB **grid, TArb arb, int size, int x, int y) {
    if (arb->type) {
        for (int i = x; i < x + size; i++) {
            for (int j = y; j < y + size; j++) {
                grid[i][j].red      = arb->data.red - 60; 
                grid[i][j].green    = arb->data.green; 
                grid[i][j].blue     = arb->data.blue; 
            }
        }
    } else {
        makeMatrix(grid, arb->sts, size/2, x, y);
        makeMatrix(grid, arb->drs, size/2, x, y + size/2);
        makeMatrix(grid, arb->drj, size/2, x + size/2, y + size/2);
        makeMatrix(grid, arb->stj, size/2, x + size/2, y);
    }
}
void task3(FILE *in, FILE *out) {
    unsigned int size = 0;
    fread(&size, sizeof(unsigned int), 1, in);
    fprintf(out, "P6\n");
    fprintf(out, "%u %u\n255\n", size, size);

    TArb arb = initArb();
    readNod(&arb, in);
    TCoada *Q = initQ();
    addCell(Q, arb);
    // daca arb->type == 1 ar trb sa scriu direct matricea;

    while (Q->inc) {
        if (! Q->inc->info->type) {     /* daca am nod neterminal */
            /* initializez copiii nodului */
            Q->inc->info->sts = initArb();
            Q->inc->info->drs = initArb();
            Q->inc->info->drj = initArb();
            Q->inc->info->stj = initArb();
            /* citesc valorile pentru copii */
            readNod(&(Q->inc->info->sts), in);
            readNod(&(Q->inc->info->drs), in);
            readNod(&(Q->inc->info->drj), in);
            readNod(&(Q->inc->info->stj), in);
            /* adaug copiii in coada */
            addCell(Q, Q->inc->info->sts);
            addCell(Q, Q->inc->info->drs);
            addCell(Q, Q->inc->info->drj);
            addCell(Q, Q->inc->info->stj);
        }
        extrQ(Q);
    }
    
    RGB **grid = (RGB **) malloc(size * sizeof(RGB *));
    for (int i = 0; i < size; i++) {
        grid[i]= malloc(size * sizeof(RGB));
    }
    makeMatrix(grid, arb, size, 0, 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fwrite(&(grid[i][j].red), sizeof(unsigned char), 1, out);
            fwrite(&(grid[i][j].green), sizeof(unsigned char), 1, out);
            fwrite(&(grid[i][j].blue), sizeof(unsigned char), 1, out);

        }
    }
}