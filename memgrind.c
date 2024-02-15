#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"


int main(int argc, char **argsv) {
    int *piarr[512];
    
    struct timeval stop, start;

    gettimeofday(&start, NULL);

    //do stuff
    for (int i = 0; i<128; i++)
    {
        piarr[i] = (int *) malloc(24);
        *(piarr[i]) = i;
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    return 0;
}

