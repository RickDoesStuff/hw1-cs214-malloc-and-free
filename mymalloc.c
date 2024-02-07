#include <stdlib.h>
#include "mymalloc.h"

#include "freelist.h"
#include "chunk.h"

#define MEMLENGTH 512
#define HEADER 8

static double memory[MEMLENGTH];

struct __freelist *head = NULL;

void *mymalloc(size_t size, char *file, int line) {
    printf(size);
    size = ((size + 8 -1) / 8 )* 8;
    printf(size);
    //fullsize=HEADER+size;
    //char *heapstart = (char *) memory;


    
    //char *byte200 = heapstart + 200;


}


void myfree(void *ptr, char *file, int line) {

}