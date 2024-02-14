#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

#include "chunk.h"
#include "chunkhead.h"

#ifdef __TEST 
#define __TEST 1
#endif
#define TEST if(__TEST)
#define LOG printf

void test_check(void *ptr) {
	if (ptr == NULL) {
		LOG("TEST PASSED\n");
	}
}