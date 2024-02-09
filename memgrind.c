#include <stdio.h>
#include "mymalloc.h"



int main(int argc, char **argsv) {

    malloc(20*sizeof(int));

    printf("\n------------------------\nnew\n------------------------\n\n");
    malloc(3*sizeof(double));

    printf("\n------------------------\nnew\n------------------------\n\n");

    malloc(15*sizeof(char));

    return 0;
}