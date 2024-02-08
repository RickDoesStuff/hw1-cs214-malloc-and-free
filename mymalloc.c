#include <stdlib.h>
#include "mymalloc.h"

#include "chunk.h"

#define MEMLENGTH 512
#define HEADER 8

static double memory[MEMLENGTH]; //4096 bytes, 512 doubles

#define HEAP ((char*)memory)
//#define METADATA ((char*)memory)

void *mymalloc(size_t size, char *file, int line) {
    // size can never be 0!! 0 size means initalize!
    if (((struct chunkhead *)HEAP)->size==0) {
        printf("NULL\n");
        // init header
        struct chunk currentchunk={{4096-8,0},NULL};
        struct chunk *pcurrentchunk = (struct chunk *)HEAP;
        *pcurrentchunk = currentchunk;

        //struct chunkhead metadata = *pcurrentchunk->head;
        printf("pcurrChunk:%i,%i\n",pcurrentchunk->head.inuse,pcurrentchunk->head.size);
    } else {
        printf("NOT NULL\n");
    }

    printf("size:%i\n",(((chunkhead *)HEAP)->size));
    printf("inuse:%i\n",(((chunkhead *)HEAP)->inuse));

    printf("HEAP start:%c\n",*HEAP);

    printf("size before:%i\n",(int)size);
    size = (size+7) & ~7;
    printf("size after:%i\n",(int)size);
    //fullsize=HEADER+size;
    //char *heapstart = (char *) memory;


    
    //char *byte200 = heapstart + 200;
    return 0;
}


void myfree(void *ptr, char *file, int line) {

}