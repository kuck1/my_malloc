#define MY_MEMORY
#include "my_memory.h"
#include <stdlib.h>
#include <stdio.h>

#define META_DATA_SIZE (32)


static struct malloc_stc * head;
static struct malloc_stc * tail;
static int stoarage_bytes;
static int blocks_used;
static int blocks_free_count
;
static int space;

struct malloc_stc
{
    bool free;
    int size;
    struct malloc_stc * next;
    struct malloc_stc * prev;
    void * buffer;
};

// Malloc Init
void my_malloc_init() {
    head = get_first_block();              
    tail = head;

    stoarage_bytes = 0;
    blocks_used = 0;
    blocks_free_count = 0;
    space = 0;
}

// Malloc Reset
void my_malloc_reset() {
    head = reset_first_block();              
    tail = head;

    stoarage_bytes = 0;
    blocks_used = 0;
    blocks_free_count = 0;
    space = 0;
}


// Malloc
void * my_malloc(int size) {
	struct malloc_stc * new_block = find_block_from_tail(size);
	new_block->free = false;
	new_block->size = size;

	//set_end();
	void * buffer = new_block->buffer;

	set_tail_on_malloc(new_block);

	return buffer;
}

struct malloc_stc * find_block(int size){
	struct malloc_stc * curr = head;
	while (!curr->free || size > curr->size){
		if(!curr->next){
			return NULL;
		}
		curr = curr->next;
	}

	divide_block(curr, size);
	
	curr->free = false;
	
	return curr;
}

struct malloc_stc * find_block_from_tail(int size){
	struct malloc_stc * curr = tail;

	while (!curr->free || size > curr->size){
		if(!curr->next){
			printf("ALLOCATION FAILED: RETURNING NULL\n");
			return NULL;
		}
		curr = curr->next;
	}

	divide_block(curr, size);
	
	curr->free = false;
	
	return curr;
}

void set_tail_on_malloc(struct malloc_stc * curr_block){
	struct malloc_stc * prev_block = get_previous_block(curr_block);
	// printf("prev_block: %d\n", prev_block);
	if(tail->prev == prev_block){
		tail = curr_block->next;
	}
}

void set_tail_on_free(struct malloc_stc * curr_block){
	if(tail->prev == curr_block){

		struct malloc_stc * prev_block = get_previous_block(curr_block);
		if(prev_block == NULL){
			tail = head;
		}
		else{
			tail = prev_block->next;
		}
	}
}

struct malloc_stc * get_previous_block(struct malloc_stc * curr){
	if(!curr->prev){
		return NULL;
	}

	curr = curr->prev;
	while(curr->free && curr->prev){
		curr = curr->prev;
	}
	if(curr->free){
		return NULL;
	}
	return curr;
}

// Free 
void my_free(void * buffer){
	
	struct malloc_stc * block = get_meta_block(buffer);

	block->free = true;
	set_tail_on_free(block);
}

// Free Helpers
struct malloc_stc * get_meta_block(void * buffer){
	char * block = buffer;
	struct malloc_stc * meta = (struct malloc_stc *) (block - META_DATA_SIZE);
	return meta;
}


// Private Variable Getters

int bytes_allocated(){
	return stoarage_bytes;
}

int blocks_allocated(){
	return blocks_used;
}

int blocks_free(){
	return blocks_free_count;
}

int space_used(){
	return space;
}


// *** POINTER LOGIC *** //

// Meta data size
// 2 boolean (1)
// 1 integer (4)
// 3 pointers (8)  

struct malloc_stc * get_first_block(){
	void * block = malloc(MAX_MALLOC_SIZE);

	struct malloc_stc * meta = (struct malloc_stc *) block;

	meta->free = true;
	meta->size = MAX_MALLOC_SIZE - META_DATA_SIZE;
	meta->next = NULL;
	meta->prev = NULL;
	meta->buffer = block + META_DATA_SIZE;

	return meta;
}

struct malloc_stc * reset_first_block(){
	void * block = head;

	struct malloc_stc * meta = (struct malloc_stc *) block;

	meta->free = true;
	meta->size = MAX_MALLOC_SIZE - META_DATA_SIZE;
	meta->next = NULL;
	meta->prev = NULL;
	meta->buffer = block + META_DATA_SIZE;

	return meta;
}

// = 30 bytes = 176 bits

void divide_block(struct malloc_stc * block, int size){
	// divide block
	char * curr = (char *) block;

	if (block->size - size < META_DATA_SIZE * 2){
		return;
	}

	struct malloc_stc * new_block = (struct malloc_stc *) (curr + META_DATA_SIZE + size);

	new_block->prev = block;
	new_block->next = block->next;
	new_block->size = (block->size - size) - META_DATA_SIZE;
	new_block->free = true;
	new_block->buffer = (curr + 2 * META_DATA_SIZE + size);

	block->size = size;
	block->next = new_block;
}

void print_blocks(){
	struct malloc_stc * curr = head;

	printf("Head: %d, Tail: %d\n", head, tail);

	while(curr && curr->size > 0){
		printf("block: %d\n", curr);
		printf("\t size: %d\n", curr->size);
		printf("\t free: %d\n", curr->free);
		printf("\t next: %d\n", curr->next);
		printf("\t prev: %d\n", curr->prev);
		printf("\t buff: %d\n\n", curr->buffer);
		curr = curr->next;
	}

	if(curr){
		printf("\nERROR:\n");
		printf("block: %d\n", curr);
		printf("\t size: %d\n", curr->size);
		printf("\t free: %d\n", curr->free);
		printf("\t next: %d\n", curr->next);
		printf("\t prev: %d\n", curr->prev);
		printf("\t buff: %d\n\n", curr->buffer);
	}
}

void update_stats(){
	struct malloc_stc * curr = head;

	stoarage_bytes = 0;
    blocks_used = 0;
    blocks_free_count = 0;
    space = 0;

	while(curr != tail){
		if(!curr->free){
			stoarage_bytes += curr->size;
			blocks_used ++;
		}
		else{
			blocks_free_count ++;
		}
		space += curr->size;
		curr = curr->next;
	}
}

