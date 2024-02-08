#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

/**
 * size:int
 * inuse:int
*/
typedef struct chunkhead {
	// head
	int size; // 4 bytes
	int inuse; // 4 bytes (just 1 or 0)
}chunkhead;
#endif
