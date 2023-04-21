#include "header.h"

int frunze(TArb arb) {
    if (! arb) return 0;
    if (arb->type) return 1;

    return frunze(arb->sts) + frunze(arb->drs) + frunze(arb->stj) + frunze(arb->drj);
}
int nrNiv(TArb arb)           /* numar niveluri (0 pentru arbore vid) */
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
int nrNivMin(TArb arb)
{
	int nss, nds, nsj, ndj, min = nrNiv(arb);
	if (!arb) return 0;
	nss = nrNiv(arb->sts); nds = nrNiv(arb->drs);
    nsj = nrNiv(arb->stj); ndj = nrNiv(arb->drj);
    if (nss < min) min = nss;
    if (nsj < min) min = nsj;
    if (nds < min) min = nds;
    if (ndj < min) min = ndj;
	return 1 + min;
}

void task1(RGB **grid, unsigned int size, unsigned int factor, FILE *out) {
    TArb img = makeArb(grid, 0, 0, size, factor);
    //printf("%lf", average(grid, 0, 0, size));
    fprintf(out, "%d\n", nrNiv(img));
    fprintf(out, "%d\n", frunze(img));
    fprintf(out, "%d\n", size / (1 << (nrNivMin(img)-1)));
}