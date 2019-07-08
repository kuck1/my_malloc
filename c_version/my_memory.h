#if !defined(MY_MALLOC_H)
#define MY_MALLOC_H
#include <stdbool.h>
#include <time.h>

#define MAX_MALLOC_SIZE (1024*1024*16)

void my_malloc_init();
void my_malloc_reset();
void* my_malloc(int size);
void my_free(void *buffer);

// Helper Functions
struct malloc_stc * find_block(int size);
struct malloc_stc * find_block_from_tail(int size);
struct malloc_stc * get_meta_block(void * buffer);
void set_tail_on_malloc(struct malloc_stc * curr_block);
void set_tail_on_free(struct malloc_stc * curr_block);
struct malloc_stc * get_previous_block(struct malloc_stc * curr);


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
void update_stats();
struct time_stc * get_time_info();

struct time_stc
{
	clock_t start;
	clock_t end;

	int find_block_time;
	int set_tail_time;
};

#endif