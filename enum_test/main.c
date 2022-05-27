#include <stdio.h>

#define PACKED __attribute__ ((packed))

typedef enum {
	TEST_ONE,
	TEST_TWO,
	TEST_THREE
} enum_test1_m;

typedef enum {
    T2_ONE,
    T2_TWO,
    T2_THREE
}PACKED enum_test2_m;

typedef enum {
	T3_ONE,
	T3_TWO,
	T3_OTHER=256
}PACKED enum_test3_m;

int main(int argc, char *argv[])
{
	enum_test1_m t1;
	enum_test2_m t2;
	enum_test3_m t3;

	printf("t1 size = %d\n", sizeof(t1));
	printf("t2 size = %d\n", sizeof(t2));
	printf("t3 size = %d\n", sizeof(t3));
}
