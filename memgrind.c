#include <stdio.h>
#include "mymalloc.h"



int main(int argc, char **argsv) {

    int *parrint = malloc(5*sizeof(int));

    printf("\n------------------------\nnew\n------------------------\n\n");
    double *pdarrmalloc = malloc(3*sizeof(double));

    printf("\n------------------------\nnew\n------------------------\n\n");

    char *name = malloc(15*sizeof(char));

    printf("\n\nMalloc done\n\n");
    parrint[0]=1;
    parrint[1]=54;
    parrint[2]=23;
    parrint[3]=99;
    parrint[4]=8;

    for(int i=0; i<5;i++)
    {
        printf("parrint[%i]\n",parrint[i]);
    }

    return 0;
}