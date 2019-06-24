#define MY_MEMORY
#include "memory_test.h"
#include "my_memory.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	my_malloc_init();

	printf("Running tests \n");

	simple_test_1();
	simple_test_2();
	simple_test_3();

}

void assert_check(int bytes, int blocks, int space, int test, int check){
	int score = 0;
	score += (bytes_allocated() == bytes);
	score += (blocks_allocated() == blocks) * 2;
	score += (space_used() == space) * 4;
	
	if (score > 0)
		printf("Test %d, check %d, failed: %d", test, check, score);
}

void simple_test_1(){
	void * buffer = my_malloc(10);
	printf("10 allocated");
	assert_check(10,1,10,1,1);
	printf("10 checked");

	my_free(buffer);
	assert_check(0,0,0,1,2);
	
	printf("Test 1 complete");
}

void simple_test_2(){
	void * buffer1 = my_malloc(10);
	my_free(buffer1);

	void * buffer2 = my_malloc(20);
	assert_check(20,1,20,2,1);
	my_free(buffer2);
	assert_check(0,0,0,2,2);

	void * buffer3 = my_malloc(30);
	assert_check(30,1,30,2,3);
	my_free(buffer3);
	assert_check(0,0,0,2,4);

	printf("Test 2 complete");
}

void simple_test_3(){
	void * buffer1 = my_malloc(10);
	void * buffer2 = my_malloc(20);
	void * buffer3 = my_malloc(30);
	
	assert_check(60,3,60,3,1);

	my_free(buffer1);
	assert_check(50,2,60,3,2);
	my_free(buffer2);
	assert_check(30,1,60,3,3);
	my_free(buffer3);
	assert_check(0,0,0,3,4);

	printf("Test 3 complete");
}
