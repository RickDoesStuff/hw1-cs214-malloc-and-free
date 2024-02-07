#include <stdlib.h> // For size_t



// Structure for the free list
typedef struct __freelist {
    int payload; // 4 bytes
    struct __freelist* next; // Pointer to the next node
} freelist;

// Function prototypes
int pop_list(freelist* dest);
void push(int item);