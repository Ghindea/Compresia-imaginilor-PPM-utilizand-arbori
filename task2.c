#include "header.h"

void task2(TArb arb, unsigned int *size, FILE *out) {
    TCoada *Q = initQ();
    addCell(Q, arb);
    fwrite(size, sizeof(unsigned int), 1, out);

    while (Q->inc) {
        /* inserare copii in coada */
        if (Q->inc->info->sts) addCell(Q, Q->inc->info->sts);
        if (Q->inc->info->drs) addCell(Q, Q->inc->info->drs);
        if (Q->inc->info->drj) addCell(Q, Q->inc->info->drj);
        if (Q->inc->info->stj) addCell(Q, Q->inc->info->stj);
        /* procesare */
        fwrite(&(Q->inc->info->type), sizeof(unsigned char), 1, out);
        if (Q->inc->info->type) {
            fwrite(&(Q->inc->info->data.red),   sizeof(unsigned char), 1, out);
            fwrite(&(Q->inc->info->data.green), sizeof(unsigned char), 1, out);
            fwrite(&(Q->inc->info->data.blue),  sizeof(unsigned char), 1, out);
        }
        /* extragere */
        extrQ(Q);
    }
}