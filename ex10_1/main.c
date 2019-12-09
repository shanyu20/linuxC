#include <stdio.h>

int add_range(int low, int high)
{
	int i, sum;
	for (i=low; i<=high; i++) {
		sum += i;
	}
	return sum;
}

int main(void)
{
	int result[100];

	result[0] = add_range(0, 10);
	result[1] = add_range(0, 100);
	printf("result[0]=%d, result[1]=%d\n",
		result[0], result[1]);
	return 0;
}
