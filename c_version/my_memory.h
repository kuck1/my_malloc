#if !defined(MY_MALLOC_H)
#define MY_MALLOC_H
#include <stdbool.h>

#define MAX_MALLOC_SIZE (1024*1024*16)

void my_malloc_init();
void my_malloc_reset();
void* my_malloc(int size);
void my_free(void *buffer);

// Helper Functions
struct malloc_stc * find_block(int size);
void set_end_from_free(struct malloc_stc * block);
struct malloc_stc * get_meta_block(void * buffer);
void set_end_from_malloc(struct malloc_stc * block);
void set_end();

// Private Variable Getters
int bytes_allocated();
int blocks_allocated();
int blocks_free();
int space_used();


// --- Pointer Logic --- //

void divide_block(struct malloc_stc * block, int size);
struct malloc_stc * get_first_block();
struct malloc_stc * reset_first_block();

// Meta Data Setters
// void set_end(void * block, bool end);
// void set_free(void * block, bool free);
// void set_size(void * block, int size);
// void set_next(void * block, void * next);
// void set_prev(void * block, void * prev);

// // Meta Data Getters
// bool is_end(void * block);
// bool is_free(void * block);
// int get_size(void * block);
// void * next_block(void * block);
// void * prev_block(void * block);

/* optional for debugging */
void print_blocks();		


#endif