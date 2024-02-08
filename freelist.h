#include <stdlib.h> // For size_t



// Structure for the free list
typedef struct __freelist {
    struct chunk payload; // 4 bytes
    struct __freelist* next; // Pointer to the next node
} __freelist;

// Function prototypes
<<<<<<< Updated upstream
int pop_list(freelist* dest);
void push(int item);
=======
double pop_list(__freelist* dest);
void push(double item, __freelist* dest);
#endif
>>>>>>> Stashed changes
