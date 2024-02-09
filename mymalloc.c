#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"

#include "chunk.h"

#define MEMLENGTH 512
#define HEADER 8

#define mallocError(s) __mallocError(s, file, line)



//#ifndef DEBUG
#define DEBUG 1
//#endif


static double memory[MEMLENGTH]; //4096 bytes, 512 doubles

#define HEAP ((char *)memory)

/**
 * View the heap
*/

// cursor-HEAP+4096
void viewHeap() 
{
    struct chunkhead *viewcursor = (chunkhead *) HEAP;
    while(viewcursor < (chunkhead *)(HEAP+(MEMLENGTH*8)-8))
    {
        if((viewcursor->size>0 && viewcursor->inuse==0) || viewcursor->inuse == 1)
        {
            printf("\n\n");
            printf("address | %p\n", viewcursor);
            printf("SIZE    | %i\n", viewcursor->size);
            printf("INUSE   | %i\n", viewcursor->inuse);
            printf("PAYLOAD | \n");

            int count = viewcursor->size/8;

            while(count > 0){
                // when count is equal is divisable by 10
                if(count % 16 == 0)
                {
                    printf("\n");
                }
                printf("-");
                count-=1;
            }
        
            printf("\nend of chunk\n\n");
        }
        viewcursor=(chunkhead *) (((char *)viewcursor)+(viewcursor->size+8));
    }
    
    printf("\nView complete\n\n\n");
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
    if (DEBUG) printf("\n\nRequested size:%i\n\n",size);
    //size can never be 0!! 0 size means initalize!
    if (((struct chunkhead *)HEAP)->size==0 && ((struct chunkhead *)HEAP)->inuse==0 ) 
    {
        // init heap
        struct chunk tempchunk={{4096-8,0},NULL};
        struct chunk *metadata = (chunk *)HEAP;
        *metadata = tempchunk; // put meta data at the start of the heap
        if (DEBUG) printf("init heap::inuse=%i::size=%i\n",metadata->head.inuse,metadata->head.size);
    }

    // Exit Program if size requested is bigger than maximum size
    if(size>(MEMLENGTH*8)-8)
    {
        mallocError("To much memory requested!");
        return NULL; 
    }
    if (DEBUG) printf("\n\nvalid memory request\nCurrent Heap before changes made\n");
    if (DEBUG) viewHeap();
    

    char *cursor = HEAP;
    char *bestFitPointer;
    int bestFitSize=9999;

    while(cursor < (HEAP+(MEMLENGTH*8)-8)) 
    {
        // not in use
        if (DEBUG) printf("address getting scanned:%p\n",cursor);

        // if current chunk is the exact size
        if (((chunkhead *)cursor)->size==size)
        {
            if (DEBUG) printf("cursor->size{%i}==size{%i}\n",((chunkhead *)cursor)->size,size);
            bestFitPointer=cursor;
            bestFitSize=((chunkhead *)cursor)->size;
            break;
        }

        // if the chunk is currently in use or
        // the current chunk size is smaller than required size
        if (((chunkhead *)cursor)->inuse==1 || ((chunkhead *)cursor)->size<size)
        {   
            if (DEBUG)
            {
                printf("((chunkhead *)cursor)->inuse{%i}==1\t",((chunkhead *)cursor)->inuse);
                printf("((chunkhead *)cursor)->size{%i}<size{%i}\n",((chunkhead *)cursor)->size,size);
            }
            cursor=cursor+8+((chunkhead *)cursor)->size;
            continue;
        }


        // if current chunk is smaller than bestFitSize
        if ((((chunkhead *)cursor)->size) < bestFitSize)
        {
            if (DEBUG) printf("((chunkhead *)cursor)->size{%i}<bestFitSize{%i}\n",((chunkhead *)cursor)->size,bestFitSize);
            if (DEBUG) printf("cursor{%p}\n",cursor);
            bestFitPointer=cursor;

            if (DEBUG) printf("((chunkhead *)cursor)->size{%i}\n",((chunkhead *)cursor)->size);
            bestFitSize=((chunkhead *)cursor)->size;

            
            if (DEBUG) printf("cursor+=((chunkhead *)cursor)->size{%p}\n",(cursor+(((chunkhead *)cursor)->size)+8));
            cursor=cursor+8+((chunkhead *)cursor)->size;
            continue;

        }


        if (DEBUG) printf("test\n\n");
        printf("ERROR, I SHOULDNT BE HERE\tPLEASE FIX\n%p\n",cursor);
        exit(1);
        cursor=cursor+8+((chunkhead *)cursor)->size;


        // increase to the start of the next meta data
    }
    if (DEBUG) printf("Exited Search Loop\n");

    // check if bestFit hasnt been found
    if(bestFitSize == 9999)
    {
        mallocError("Not enough memory. Memory fragmentation.");
        return NULL;
    }

    // we have found best fit or exact fit
    // create a chunk head to put the meta data in
    struct chunkhead tempcurrentchunk = {size,1};
    // create a pointer of the chunk head type to the bestffit address in memory
    struct chunkhead *currentmetadata = (chunkhead *)bestFitPointer;
    // at that point in memory (the meta data area), input the tempcurrentchunk data.
    *currentmetadata = tempcurrentchunk; // put meta data at specific point in the heap

    if (DEBUG) printf("Created currentchunk meta data\ninuse{%i}::size{%i}::pointer{%p}\n",
                            currentmetadata->inuse,currentmetadata->size,(char *)currentmetadata);
    if (DEBUG) printf("CREATED CURRENT CHUNK META DATA\n");
    if (DEBUG) viewHeap();
    // cursorsize-size+bestpointersize    
    // bestFitPointer+
    // HEAP+distanceintoheap=cursor

    // for trailing chunk
    // ex: 
    // heap = 100000
    // bestFitPointer = 100400 
    // this means we are 400 bytes into the heap
    // we need to subtract that from 4096 to see how much remaining data is in the heap
    // then subtract 8 for the new meta data

    // THIS WON'T WORK WHEN WE START FREEING MEMORY THAT IS HAS IN USE CHUNKS AFTER IT!!
    // we will get override errors bc we don't know how much memory is actually free after it is allocated

    // distanceIntoHeap how big the last chunk was
    // ((size+8)+(size2+8)+(size3+8)...)
    int distanceIntoHeap = (bestFitPointer-HEAP)+size+8;
    if (DEBUG) printf("distanceIntoHeap{%i}\n",distanceIntoHeap);

    // quick way to calculate the remaining free bytes
    int sizeOfRemainingFree = 4096 - distanceIntoHeap-8;
    if (DEBUG) printf("sizeOfRemainingFree{%i}\n",sizeOfRemainingFree);

    struct chunkhead temptrailingchunk={sizeOfRemainingFree,0};

    // we need it to start at the first byte of the new chunk
    struct chunkhead *trailingmetadata = (chunkhead *) (HEAP+distanceIntoHeap);

    *trailingmetadata = temptrailingchunk; // put meta data after current chunk / start of next chunk

    if (DEBUG) printf("trailing metadata::inuse=%i::size=%i::address={%p}\n",
                        trailingmetadata->inuse,trailingmetadata->size,(char *)trailingmetadata);
    
    if (DEBUG) printf("\n\nTrailing metadata added to heap\n");
    if (DEBUG) viewHeap();

    if (DEBUG) printf("HEAP+distanceIntoHeap::inuse=%i::size=%i::address={%p}\n",
                        ((chunkhead *)HEAP+distanceIntoHeap)->inuse,
                        ((chunkhead *)HEAP+distanceIntoHeap)->size,
                        (char *)(chunkhead *)(HEAP+distanceIntoHeap));

    return (void *) (bestFitPointer+8);

}


void myfree(void *ptr, char *file, int line) {

}
