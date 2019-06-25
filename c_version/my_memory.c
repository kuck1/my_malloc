#define MY_MEMORY
#include "my_memory.h"
#include <stdlib.h>
#include <stdio.h>

#define META_DATA_SIZE (32)


static void * head;
static int bytes;
static int blocks_used;
static int blocks_free;
static int space;

struct malloc_stc
{
    bool end;
    bool free;
    int size;
    struct malloc_stc * next;
    struct malloc_stc * prev;
    struct void * buffer;
};

// Malloc Init
void my_malloc_init() {
    head = get_first_block();              

    bytes = 0;
    blocks_used = 0;
    blocks_free = 1;
    space = 0;
}

// Malloc
void * my_malloc(int size) {
	void * new_block = find_block(size);

	set_size(new_block, size);
	set_end_from_malloc(new_block);
	set_free(new_block, false);

	bytes += size;
	blocks_used += 1;

	if (is_end(new_block)) {
		space += size;
	}

	return new_block;
}

// Malloc Helpers 
void set_end_from_malloc(void * block){
	if (is_end(prev_block(block)) && is_free(next_block(block))){
		set_end(prev_block(block), false);
		set_end(block, true);
	}
}

void * find_block(int size){
	void * curr = head;

	while (!is_free(curr) || size > get_size(curr)){
		curr = next_block(head);
	}

	divide_block(curr, size);

	return curr;
}


// Free 
void my_free(void * block){
	set_free(block, true);

	int size = get_size(block);
	bytes -= size;
	blocks_used -= 1;
	blocks_free += 1;

	if(is_end(block)){
		space -= size;
		set_end_from_free(block);
	}
}

// Free Helpers
void set_end_from_free(void * block){
	void * curr = block;

	while (is_free(curr))
		curr = prev_block(curr);

	set_end(curr, true);
}

// Private Variable Getters

int bytes_allocated(){
	return bytes;
}

int blocks_allocated(){
	return blocks_used;
}

int blocks_free_count(){
	return blocks_free;
}

int space_used(){
	return space;
}


// *** POINTER LOGIC *** //

// Meta data size
// 2 boolean (1)
// 1 integer (4)
// 3 pointers (8)  

void * get_first_block(){
	char * block = malloc(MAX_MALLOC_SIZE);

	struct malloc_stc meta = block;

	meta->end = true;
	meta->free = true;
	meta->size = MAX_MALLOC_SIZE - META_DATA_SIZE;
	meta->next = NULL;
	meta->prev = NULL;
	meta->buffer = block + META_DATA_SIZE;

	return meta;
}

// = 30 bytes = 176 bits

void divide_block(void * block, int size){
	// divide block
}

// Meta Data Setters 

void set_end(void * block, bool end){
	char * curr = block;
	char * new = curr - 22;

	new = end;
}

void set_free(void * block, bool free){
	// set free
}

void set_size(void * block, int size){
	// set size
}

void set_next(void * block, void * next){
	// set next
}

void set_prev(void * block, void * prev){
	// set prev
}

// Meta Data Getters

bool is_end(void * block){
	// return if end
}

bool is_free(void * block){
	// return if free
}

int get_size(void * block){
	// return size
}

void * next_block(void * block){
	// return next
}

void * prev_block(void * block){
	// return prev
}

