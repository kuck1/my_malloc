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
struct malloc_stc * get_meta_block(void * buffer);

// Private Variable Getters
int bytes_allocated();
int blocks_allocated();
int blocks_free();
int space_used();


// --- Pointer Logic --- //
void divide_block(struct malloc_stc * block, int size);
struct malloc_stc * get_first_block();
struct malloc_stc * reset_first_block();

/* optional for debugging */
void print_blocks();		


#endif