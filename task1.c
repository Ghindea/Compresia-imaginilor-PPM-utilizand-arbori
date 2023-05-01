/* GHINDEA DANIEL-TEODOR 315CB */

#include "header.h"

int frunze(TArb arb) {             // determinarea nr de frunze
    if (! arb) return 0;
    if (! arb->sts && ! arb->drs && ! arb->drj && ! arb->stj) return 1;

    return frunze(arb->sts) + frunze(arb->drs) + frunze(arb->drj) + frunze(arb->stj);
}
int nrNiv(TArb arb)                // determinarea numarului de nivele
{
	int nss, nds, nsj, ndj, max = 0;
	if (!arb) return 0;
	nss = nrNiv(arb->sts); nds = nrNiv(arb->drs);
    nsj = nrNiv(arb->stj); ndj = nrNiv(arb->drj);
    if (nss > max) max = nss;
    if (nsj > max) max = nsj;
    if (nds > max) max = nds;
    if (ndj > max) max = ndj;
	return 1 + max;
}
int nrNivMin(TArb arb, int niv) {   // determinarea nivelului minim ce contine o frunza
	if (! arb) return 0;
    if (arb->type) {
        return niv;
    }
    int mnss = nrNivMin(arb->sts, niv+1);
    int mnds = nrNivMin(arb->drs, niv+1);
    int mndj = nrNivMin(arb->drj, niv+1);
    int mnsj = nrNivMin(arb->stj, niv+1);

    int max = 100;
    if (mnss < max) max = mnss;
    if (mnds < max) max = mnds;
    if (mndj < max) max = mndj;
    if (mnsj < max) max = mnsj;

    return max;
}

void task1(RGB **grid, unsigned int size, unsigned int factor, FILE *out) {
    TArb img = makeArb(grid, 0, 0, size, factor);
    int nrLv = nrNiv(img), leaf = frunze(img), maxDim = size / (1 << nrNivMin(img, 0));

    /* afisare */
    fprintf(out, "%d\n", nrLv);
    fprintf(out, "%d\n", leaf);
    fprintf(out, "%d\n", maxDim);

    /* curatare */
    cleanArb(img);
}