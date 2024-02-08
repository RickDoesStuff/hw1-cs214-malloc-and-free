#include <stdio.h>
#include "mymalloc.h"



int main(int argc, char **argsv) {

    malloc(3*sizeof(char));

    printf("\n\n\n------------------------\nnew\n------------------------\n\n");

    malloc(15*sizeof(char));

    return 0;
}