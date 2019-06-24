#if !defined(MY_MALLOC_H)
#define MY_MALLOC_H
#include <stdbool.h>

#define MAX_MALLOC_SIZE (1024*1024*16)

void my_malloc_init();
void* my_malloc(int size);
void my_free(void *buffer);

// Helper Functions
void set_end_from_malloc(void * block);
void * find_block(int size);
void set_end_from_free(void * block);

// Private Variable Getters
int bytes_allocated();
int blocks_allocated();
int blocks_free_count();
int space_used();

// Meta Data Setters
void set_end(void * block, bool end);
void set_size(void * block, int size);
void set_free(void * block, bool free);
void set_next(void * block, void * next);
void set_prev(void * block, void * prev);

// Meta Data Getters
bool is_end(void * block);
int get_size(void * block);
bool is_free(void * block);
void * next_block(void * block);
void * prev_block(void * block);

/* optional for debugging */
void print_my_malloc_free_list();		


#endif