#include <stdio.h>
#include "mymalloc.h"

void bookTest(){
        
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


    free(parrint);
    free(pnewddouble);
}

int main(int argc, char **argsv) {
    //bookTest();
    int *piarr[512];
    for (int i = 0; i<8; i++)
    {
        printf("piarr[%i]\n",i);
        piarr[i] = (int *) malloc(248+256);
    }
    
    // free invalid memory
    // printf("\n\nfree[15]+16\n");
    // free(piarr[15]+16);
    // test passes


    // free'ing already free'd test
    // int *piarr=piarr[1];
    // printf("\n\nfree[1]\n");
    // free(piarr[1]);
    // printf("\n\nfree[1] again\n");
    // free(piarr15[1]);
    // test passes

    // free memory not in heap
    // int test = 5;
    // int *ptest = &test;
    // free(ptest);
    // test passes

    // free memory not in heap
    // free(piarr[15]+128);
    // passes

    // test free first then the following chunk
    // free(piarr[0]);
    // free(piarr[1]);
    // passes

    // free 0, 2, then 1
    // free(piarr[0]);
    // free(piarr[2]);
    // free(piarr[1]);
    // passes

    // free 2, 4, then 3 in the middle of the heap
    // free(piarr[2]);
    // free(piarr[4]);
    // free(piarr[3]);
    // passes


    // free 2, 4, then 3 in the middle of the heap
    // free(piarr[5]);
    // free(piarr[7]);
    // free(piarr[6]);
    // passes? most times


    // free 5, then 6 then 7
    free(piarr[5]);
    free(piarr[6]);
    free(piarr[7]);
    // passes? most times




    return 0;
    

//    for (int i=0;i<257;i++){
//         malloc(1);
//    }

}

