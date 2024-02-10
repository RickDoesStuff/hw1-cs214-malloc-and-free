#include <stdio.h>
#include "mymalloc.h"



int main(int argc, char **argsv) {
    
    int *parrint = malloc(8*sizeof(int));

    parrint[0]=1;
    parrint[1]=54;
    parrint[2]=23;
    parrint[3]=99;
    parrint[4]=8;

    printf("\n------------------------\nnew\n------------------------\n\n");
    double *pdarrmalloc = malloc(4*sizeof(double));

    printf("\n------------------------\nnew\n------------------------\n\n");

    char *name = malloc(60*sizeof(char));

    printf("\n\nMalloc done\n\n");


    for(int i=0; i<5;i++)
    {
        printf("parrint[%i]\n",parrint[i]);
    }

    free(pdarrmalloc);

    double *pnewddouble=malloc(sizeof(double));

    printf("pnewint malloc\n\n");
    int *pnewint=malloc(sizeof(int));


    return 0;
    

//    for (int i=0;i<257;i++){
//         malloc(1);
//    }

}