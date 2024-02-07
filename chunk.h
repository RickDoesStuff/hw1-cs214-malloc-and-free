#include <stdio.h>
#include <stdlib.h>

typedef struct chunk {
	// in use chunk
	double* header;
	double* payload;
};