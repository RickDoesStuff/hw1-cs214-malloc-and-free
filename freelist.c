#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "freelist.h"

typedef struct __freelist {
	struct chunk payload; // multiple of 8 bytes
	struct chunk* next; // pointer is 8 bytes
};
// struct 

/**
* Pop the head
* Uses free() from stdlib (we need our own free())
* @params the list
*
* @return int success
*/
int pop_list(struct __freelist** dest) {

	// checks if list is empty or pointer is invalid or if 
	// its free'd(might not need the mmapd/free'd check)
 	if (dest==NULL || *dest==NULL) return 0;

	struct __freelist* old = dest; // save current head
	dest = (*dest)->next; // update the head to next element
	free(old); // free old head
	return 1; // return sucess
}

/**
* Push to the head of __freelist
* @params
* int payload for head
* @return void
*/
void push(double newpayload, struct __freelist *head) {
	struct __freelist* new = malloc(sizeof(struct __freelist)); // 8 bytes

	if (new == NULL)
		return;
//	new->payload = newpayload; error
	new->next = head;
	head = new;
}

typedef struct size_t {
	unsigned long long size;
};