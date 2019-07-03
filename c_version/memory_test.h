
#if !defined(MEMORY_TEST_H)
#define MEMORY_TEST_H

int main();

void assert_check(int bytes, int blocks, int blocks_free_count, int space, int test, int check);

void simple_test_1();
void simple_test_2();
void simple_test_3();

#endif