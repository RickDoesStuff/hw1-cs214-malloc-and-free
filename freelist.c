#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "freelist.h"

// It's possible you may have made your pointers wrong
// int* x is different from int *x

/**
* Pop the head
* Uses free() from stdlib (we need our own free())
* @params the list
*
* @return int success
*/
double pop_list(struct __freelist* dest) {

	// checks if list is empty or pointer is invalid or if 
	// its free'd(might not need the mmapd/free'd check)
<<<<<<< Updated upstream
 	if (dest==NULL || *dest==NULL || (*dest)->payload.mmapd==0) return 0;
=======
 	if (dest==NULL || dest->next==NULL) return 0;
>>>>>>> Stashed changes

	struct __freelist* old = dest; // save current head
	dest = dest->next; // update the head to next element
	free(old); // free old head
	return 1; // return sucess
}

/**
* Push to the head of __freelist
* @params
* int payload for head
* @return void
*/
<<<<<<< Updated upstream
void push(int item) {
=======
void push(double newpayload, struct __freelist* head) {
>>>>>>> Stashed changes
	struct __freelist* new = malloc(sizeof(struct __freelist)); // 8 bytes

	if (new == NULL || new->payload == NULL)
		return;
	new->payload = item;
	new->next = head;
	head = new;
}

// typedef struct size_t {
// 	unsigned long long size;
// };