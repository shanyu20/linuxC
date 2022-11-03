#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRand(int range)
{
	return range ? rand()%range : rand();
}

int main(void)
{
    int i;
    time_t t;
    srand((unsigned)time(&t));
     
	// 或者 
	srand((unsigned)time(NULL)); //初始化随机数种子 
    for (i = 0; i < 10; i++)
    {
        printf("Random1 value is %d\n", getRand(5000));
    }

	for (i = 0; i < 10; i++) {
		srand(time(NULL));
		printf("Random2 value is %d\n", getRand(1000));
	}
	
    return 0;
}
