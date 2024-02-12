#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"

#include "chunk.h"
#include "chunkhead.h"

#ifdef __TEST 
#define __TEST 1
#endif
#define TEST if(__TEST)
#define LOG printf

int test_check() {
    return 0;
}


void test_myfree_valid_pointer() {
    void *ptr = malloc(8);
    myfree(ptr, __FILE__, __LINE__);
}

void test_myfree_null_pointer() {
    myfree(NULL, __FILE__, __LINE__);
}

void test_myfree_int_free() {
    void *ptr = malloc(4);
    myfree(ptr, __FILE__, __LINE__);
}

int main(int argc, char **argsv) {
    test_check();
    test_myfree_valid_pointer();
    test_myfree_null_pointer();
    test_myfree_double_free();
    return 0;
}