#include <stdio.h>

int main(void)
{
	char map[2][3] = {{1, 2, 3}, {4, 5, 6}};
	char i, j;
	char val1, val2, val3;
	
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			val1 = map[i][j];
			val2 = *(*(map + i) + j);
			val3 = (*(map + i))[j];    //不推荐
			printf("val1 = %d, val2 = %d, val3 = %d\n",
					val1, val2, val3);
		}
	}
	
	return 0;
}  