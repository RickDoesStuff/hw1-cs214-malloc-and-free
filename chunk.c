#include <stdio.h>
#include <stdlib.h>

typedef struct chunk {
	// header 8 bytes
	int size; // 4 bytes
	int inuse; // 4 bytes (just 1 or 0)

	double* payload; // multiple of 8 bytes
};