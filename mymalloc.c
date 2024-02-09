#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"

#include "chunk.h"

#define MEMLENGTH 512
#define HEADER 8

#define mallocError(s) __mallocError(s, file, line)


static double memory[MEMLENGTH]; //4096 bytes, 512 doubles

#define HEAP ((char *)memory)

/**
 * View the heap
*/

// cursor-HEAP+4096
void viewHeap() 
{
    struct chunk *cursor = (chunk *) HEAP;
    while(cursor < (chunk *)HEAP+(MEMLENGTH*8)-8)
    {
        printf("SIZE    | %i\n", cursor->head.size);
        printf("INUSE   | %i\n", cursor->head.inuse);
        printf("PAYLOAD | \n");

        int count = cursor->head.size/16;

        while(count > 0){
            // when count is equal is divisable by 10
            if(count % 16 == 0)
            {
                printf("\n");
            }
            printf("-");
            count-=1;
        }
        printf("\n");
        cursor+=(cursor->head.size)+8;        
    }
    return;
}

void __mallocError(char* msg, char *file, int line)
{
    printf("%s\n",msg);
    printf("Error (%s:%i)", file, line);
    exit(1);
}

void *mymalloc(size_t size, char *file, int line) 
{

    //size can never be 0!! 0 size means initalize!
    if (((struct chunkhead *)HEAP)->size==0 && ((struct chunkhead *)HEAP)->inuse==0 ) 
    {
        // init heap
        struct chunk tempchunk={{4096-8,0},NULL};
        struct chunk *metadata = (chunk *)HEAP;
        *metadata = tempchunk; // put meta data at the start of the heap
        printf("init heap::inuse=%i::size=%i\n",metadata->head.inuse,metadata->head.size);
    }

    // Exit Program if size requested is bigger than maximum size
    if(size>(MEMLENGTH*8)-8)
    {
        mallocError("To much memory requested!");
        return NULL; 
    }

    viewHeap();
    

    struct chunkhead *cursor = (chunkhead *) HEAP;
    char *bestFitPointer;
    int bestFitSize=9999;

    while(cursor < (chunkhead *)HEAP+(MEMLENGTH*8)-8) 
    {
        // not in use
        printf("address getting scanned:%p\n",cursor);


        // if the chunk is currently in use or
        // the current chunk size is smaller than required size
        if (((struct chunkhead *)HEAP)->inuse==1 || cursor->size<size)
        {   
            
            cursor+=(cursor->size)+8;
            continue;
        }

        // if current chunk is smaller than bestFitSize
        if ((cursor->size) < bestFitSize)
        {
            bestFitPointer=(char *) cursor;
            bestFitSize=cursor->size;

            cursor+=(cursor->size)+8;
            continue;

        }

        // if current chunk is the exact size
        if (cursor->size==size)
        {
            bestFitPointer=(char *)cursor;
            bestFitSize=cursor->size;
            break;
        }

        printf("ERROR, I SHOULDNT BE HERE\tPLEASE FIX\n%p\n",cursor);

        // increase to the start of the next meta data
    }

    // check if bestFit hasnt been found
    if(bestFitSize == 9999)
    {
        mallocError("Not enough memory. Memory fragmentation.");
        return NULL;
    }

    // we have found best fit or exact fit
    struct chunk tempchunk2 = {{size,1},NULL};
    struct chunk *metadata2 = (chunk *)bestFitPointer;
    *metadata2 = tempchunk2; // put meta data at specific point in the heap

    // cursorsize-size+bestpointersize
    
    //bestFitPointer+
    // HEAP+distanceintoheap=cursor
    int sizeOfRemainingFree = 4096 - (HEAP - bestFitPointer) - 8;

    struct chunk tempchunk={{sizeOfRemainingFree,0},NULL};
    struct chunk *metadata = (chunk *) (bestFitPointer-HEAP+8);

    *metadata = tempchunk; // put meta data at the start of the heap
    printf("init heap::inuse=%i::size=%i\n",metadata->head.inuse,metadata->head.size);
    return (void *) bestFitPointer+8;

}


void myfree(void *ptr, char *file, int line) {

}
