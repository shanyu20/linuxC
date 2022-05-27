#include <stdio.h>
#include <stdlib.h>

#define A  "Hello"
#define B  "world"
#define FUNC(arg) \
void print##arg(int arg) \
{ \
	printf(#arg" = %d\n", arg); \
}

FUNC(size);

int main(void)
{
	int size = 100;
	int temp = -20;

	printf("test"A"and"B"\n");
	printsize(size);

	printf("---------------\n");
	printf("\'hello\'\n");
	printf("'hello'\n");

	printf("data is %d\n", temp);
}
