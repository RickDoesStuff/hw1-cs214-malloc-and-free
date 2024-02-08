#ifndef CHUNK_H
#define CHUNK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct chunk {
	// in use chunk
	double* header;
	double* payload;
};
#endif
