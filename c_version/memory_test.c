#define MY_MEMORY
#include "memory_test.h"
#include "my_memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(){
	my_malloc_init();

	printf("Running tests \n\n");

	// void * warmup1 = malloc(10);
	// void * warmup2 = malloc(50);
	// void * warmup3 = malloc(100);

	// free(warmup1);
	// free(warmup2);
	// free(warmup3);
	simple_test_1();
	simple_test_2();
	simple_test_3();

	time_1();
	time_2();
	time_3();

	stress_test_1();

	stress_time_1();
	stress_time_2();
	stress_time_3();
	stress_time_4();

}

void assert_check(int bytes, int blocks, int blocks_free_count, int space, int test, int check){
	int score = 0;

	update_stats();

	score += 1 - (bytes_allocated() == bytes);
	
	score += (1 - (blocks_allocated() == blocks)) * 2;

	score += (1 - (blocks_free() == blocks_free_count)) * 4;

	score += (1 - (space_used() == space)) * 8;

	if (score > 0){
		print_blocks();
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
	assert_check(0,0,0,0,1,2);
	
	printf("Test 1 complete\n\n");
}

void time_1(){
	printf("TIME 1: ");
	clock_t start, mid, end;
	void * buffer;

	start = clock();
	buffer = my_malloc(10);
	mid = clock();
	my_free(buffer);
	end = clock();

	int my_malloc_time = mid - start;
	int my_free_time = end - mid;

	start = clock();
	buffer = malloc(10);
	mid = clock();
	free(buffer);
	end = clock();

	int malloc_time = mid - start;
	int free_time = end - mid;

	printf("Malloc: %d:%d, Free: %d:%d\n\n", my_malloc_time, malloc_time, my_free_time, free_time);
}

void simple_test_2(){
	void * buffer1 = my_malloc(10);
	my_free(buffer1);

	void * buffer2 = my_malloc(20);
	assert_check(20,1,1,30,2,1);

	my_free(buffer2);
	assert_check(0,0,0,0,2,2);

	void * buffer3 = my_malloc(30);
	assert_check(30,1,2,60,2,3);
	my_free(buffer3);
	assert_check(0,0,0,0,2,4);

	printf("Test 2 complete\n\n");
}

void time_2(){
	printf("TIME 2: ");
	clock_t start, end;
	void * buffer1;
	void * buffer2;
	void * buffer3;

	start = clock();
	buffer1 = my_malloc(10);
	my_free(buffer1);
	buffer2 = my_malloc(20);
	my_free(buffer2);
	buffer3 = my_malloc(30);
	my_free(buffer3);
	end = clock();

	int my_time = end - start;

	start = clock();
	buffer1 = malloc(10);
	free(buffer1);
	buffer2 = malloc(20);
	free(buffer2);
	buffer3 = malloc(30);
	free(buffer3);
	end = clock();

	int malloc_time = end - start;

	printf("Clocks: %d:%d\n\n", my_time, malloc_time);
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
	assert_check(0,0,0,0,3,4);

	printf("Test 3 complete\n\n");
}

void time_3(){
	printf("TIME 3: ");
	clock_t start, mid, end;
	void * buffer1;
	void * buffer2;
	void * buffer3;

	start = clock();
	buffer1 = my_malloc(10);
	buffer2 = my_malloc(20);
	buffer3 = my_malloc(30);
	mid = clock();

	my_free(buffer1);
	my_free(buffer2);
	my_free(buffer3);
	end = clock();

	int my_malloc_time = mid - start;
	int my_free_time = end - mid;

	start = clock();
	buffer1 = malloc(10);
	buffer2 = malloc(20);
	buffer3 = malloc(30);
	mid = clock();

	free(buffer1);
	free(buffer2);
	free(buffer3);
	end = clock();

	int malloc_time = mid - start;
	int free_time = end - mid;

	printf("Malloc: %d:%d, Free: %d,%d \n\n", my_malloc_time, malloc_time, my_free_time, free_time);
}

void stress_test_1(){
	my_malloc_reset();
	assert_check(0,0,0,0, 4, 0);

	void * buffer1 = my_malloc(10000);
	void * buffer2 = my_malloc(50000);
	void * buffer3 = my_malloc(100000);
	void * buffer4 = my_malloc(500000);
	void * buffer5 = my_malloc(5000000);

	assert_check(5660000,5,0,5660000, 4, 1);

	my_free(buffer1);
	my_free(buffer2);
	my_free(buffer3);
	my_free(buffer4);
	my_free(buffer5);

	assert_check(0,0,0,0, 4, 2);

	printf("Stress Test 1 complete\n\n");
}

void stress_time_1(){
	printf("Stress Time 1: ");
	my_malloc_reset();

	clock_t start, mid, end;

	start = clock();
	void * buffer1 = my_malloc(10000);
	void * buffer2 = my_malloc(50000);
	void * buffer3 = my_malloc(100000);
	void * buffer4 = my_malloc(500000);
	void * buffer5 = my_malloc(5000000);

	my_free(buffer1);
	my_free(buffer2);
	my_free(buffer3);
	my_free(buffer4);
	my_free(buffer5);

	buffer5 = my_malloc(5000000);
	buffer4 = my_malloc(500000);
	buffer3 = my_malloc(100000);
	buffer2 = my_malloc(50000);
	buffer1 = my_malloc(10000);

	end = clock();

	printf("Stress 1: %lu\n\n", end-start);
}

void stress_time_2(){
	my_malloc_reset();

	void * buffer;
	clock_t start, end, start2,end2;

	start = clock();
	for(int i = 10; i > 0; i--){
		buffer = my_malloc(1000);
	}
	end = clock();

	start2 = clock();
	for(int i = 10; i > 0; i--){
		buffer = malloc(1000);
	}
	end2 = clock();

	printf("Stress 2: %lu:%lu\n\n", end-start, end2-start2);

}


void stress_time_3(){
	my_malloc_reset();

	void * buffer;
	clock_t start, end, start2,end2;

	start = clock();
	for(int i = 1000; i > 0; i--){
		buffer = my_malloc(1000);
	}
	end = clock();

	start2 = clock();
	for(int i = 1000; i > 0; i--){
		buffer = malloc(1000);
	}
	end2 = clock();

	printf("Stress 2: %lu:%lu\n\n", end-start, end2-start2);

}

void stress_time_4(){
	my_malloc_reset();

	void * buffer;
	clock_t start, end, start2,end2;

	start = clock();
	for(int i = 10000; i > 0; i--){
		buffer = my_malloc(1000);
	}
	end = clock();

	start2 = clock();
	for(int i = 10000; i > 0; i--){
		buffer = malloc(1000);
	}
	end2 = clock();
	printf("Stress 2: %lu:%lu\n\n", end-start, end2-start2);
}
