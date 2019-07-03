#define MY_MEMORY
#include "memory_test.h"
#include "my_memory.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	my_malloc_init();

	printf("Running tests \n\n");

	// void * pointer;
	// bool boolean;
	// int integer;

	// printf("size of pointer: %lu \n", sizeof(pointer));
	// printf("size of boolean: %lu \n", sizeof(boolean));
	// printf("size of integer: %lu \n", sizeof(integer));

	// printf("Printed sizes\n");

	simple_test_1();
	simple_test_2();
	simple_test_3();

}

void assert_check(int bytes, int blocks, int blocks_free_count, int space, int test, int check){
	int score = 0;
	score += 1 - (bytes_allocated() == bytes);
	
	score += (1 - (blocks_allocated() == blocks)) * 2;

	score += (1 - (blocks_free() == blocks_free_count)) * 4;

	score += (1 - (space_used() == space)) * 8;

	if (score > 0){
		printf("Test %d, check %d, failed: %d\n", test, check, score);
		printf("bytes actual: %d bytes expected: %d\n", bytes_allocated(), bytes);
		printf("blocks allocated actual: %d blocks allocated expected: %d\n", blocks_allocated(), blocks);
		printf("blocks free actual: %d blocks free expected: %d\n", blocks_free(), blocks_free_count);	
		printf("space actual: %d space expected: %d\n\n", space_used(), space);

	}

}

void simple_test_1(){
	void * buffer = my_malloc(10);
	assert_check(10,1,0,10,1,1);

	my_free(buffer);
	assert_check(0,0,1,0,1,2);
	
	printf("Test 1 complete\n\n");
}

void simple_test_2(){
	void * buffer1 = my_malloc(10);
	my_free(buffer1);

	void * buffer2 = my_malloc(20);
	assert_check(20,1,1,30,2,1);

	my_free(buffer2);
	assert_check(0,0,2,0,2,2);

	void * buffer3 = my_malloc(30);
	assert_check(30,1,2,60,2,3);
	my_free(buffer3);
	assert_check(0,0,3,0,2,4);

	printf("Test 2 complete\n\n");
}

void simple_test_3(){
	void * buffer1 = my_malloc(10);

	void * buffer2 = my_malloc(20);

	void * buffer3 = my_malloc(30);
	
	assert_check(60,3,0,60,3,1);

	my_free(buffer1);
	assert_check(50,2,1,60,3,2);
	my_free(buffer2);
	assert_check(30,1,2,60,3,3);
	my_free(buffer3);
	assert_check(0,0,3,0,3,4);

	printf("Test 3 complete\n\n");
}
