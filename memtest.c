#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// Compile with -DREALMALLOC to use the real malloc() instead of mymalloc()
#ifndef REALMALLOC
#include "mymalloc.h"
#endif

#define MEMSIZE 4096
#define HEADERSIZE 8
#define OBJECTS 64
#define OBJSIZE (MEMSIZE / OBJECTS - HEADERSIZE)

void check_objects(char *obj[OBJECTS]) {
	int i, j, errors = 0;
	// check that all objects contain the correct bytes
	for (i = 0; i < OBJECTS; i++) {
		for (j = 0; j < OBJSIZE; j++) {
			if (obj[i][j] != i) {
				errors++;
				printf("Object %d byte %d incorrect: %d\n", i, j, obj[i][j]);
			}
		}
	}
	printf("%d incorrect bytes\n", errors);
}

void fill_objects(char *obj[OBJECTS]) {
	int i=0;
	// fill memory with objects
	for (i = 0; i < OBJECTS; i++) {
		obj[i] = malloc(OBJSIZE);
	}
	
	// fill each object with distinct bytes
	for (i = 0; i < OBJECTS; i++) {
		memset(obj[i], i, OBJSIZE);
	}

	check_objects(obj);
}

void free_every_other_object(char *obj[OBJECTS]) {
	int i=0;
	// free every other object
	for (i = 0; i < OBJECTS; i += 2) {
		free(obj[i]);
		printf("Object %d freed\n", i);
	}
	check_objects(obj);
}

void malloc_large_object(char *obj[OBJECTS]) {
	int i=0;
	for (i = 0; i < OBJSIZE; i++) {
		obj[i] = malloc(MEMSIZE/2);
		if (obj[i] == NULL) {
			printf("Cannot allocate large object\n");
		} else {
			printf("ERROR: Large object allocated\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("Large object not allocated!\n");
}

int main(int argc, char **argv)
{
	char *obj[OBJECTS];
	
	// fill memory with objects
	fill_objects(obj);

	// free every other object
	free_every_other_object(obj);

	// malloc large object when memory is fragmented
	malloc_large_object(obj);
	
	return EXIT_SUCCESS;
}
