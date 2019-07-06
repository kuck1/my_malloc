
#if !defined(MEMORY_TEST_H)
#define MEMORY_TEST_H

int main();

void assert_check(int bytes, int blocks, int blocks_free_count, int space, int test, int check);

void simple_test_1();
void simple_test_2();
void simple_test_3();

void time_1();
void time_2();
void time_3();

void stress_test_1();

void stress_time_1();
void stress_time_2();
void stress_time_3();
void stress_time_4();

#endif