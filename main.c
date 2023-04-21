#include "header.h"

int main(int argc, char *argv[])
{
	unsigned int size = 0;
    if (strstr(argv[1],"-c")) {        /* ----- Task 1 && Task2 -----*/ 
        FILE *in = fopen(argv[3], "r");
        FILE *out = fopen(argv[4], "w+");
        if (! in) {
                printf("err: cannot open input file!");
        }
        if (! out) {
                printf("err: cannot open output file!");
        }
        int factor = atoi(argv[2]);
        RGB **grid = readData(&size, in);
        if (strstr(argv[1], "-c1")) {
                task1(grid, size, factor, out);
        } else {
                TArb arb = makeArb(grid, 0, 0, size, factor);
                task2(arb, &size, out);
        }
    } else {                            /*----- Task 3 ----- */
        FILE *in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w+");
        if (! in) {
                printf("err: cannot open input file!");
        }
        if (! out) {
                printf("err: cannot open output file!");
        }
        task3(in,out);
    }
    return 0;
}
