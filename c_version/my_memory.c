#define MY_MEMORY
#include "my_memory.h"
#include <stdlib.h>
#include <stdio.h>

#define META_DATA_SIZE (32)


static struct malloc_stc * head;
static int stoarage_bytes;
static int blocks_used;
static int blocks_free_count
;
static int space;

struct malloc_stc
{
    bool end;
    bool free;
    int size;
    struct malloc_stc * next;
    struct malloc_stc * prev;
    void * buffer;
};

// Malloc Init
void my_malloc_init() {
    head = get_first_block();              

    stoarage_bytes = 0;
    blocks_used = 0;
    blocks_free_count = 0;
    space = 0;
}

// Malloc Reset
void my_malloc_reset() {
    head = reset_first_block();              

    stoarage_bytes = 0;
    blocks_used = 0;
    blocks_free_count = 0;
    space = 0;
}


// Malloc
void * my_malloc(int size) {
	struct malloc_stc * new_block = find_block(size);
	new_block->free = false;
	new_block->size = size;

	stoarage_bytes += size;
	blocks_used += 1;

	//set_end();
	void * buffer = new_block->buffer;

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


// Free 
void my_free(void * buffer){
	
	struct malloc_stc * block = get_meta_block(buffer);

	block->free = true;

	int size = block->size;
	stoarage_bytes -= size;
	blocks_used -= 1;
	blocks_free_count += 1;

	//set_end(block);
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

	meta->end = true;
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

	meta->end = true;
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


