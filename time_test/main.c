#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t t;
	struct tm *tm;
	char date[32] = {0};
	
	time(&t);
	tm = localtime(&t);
	strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
	printf("now = %s, t = %ld\n", date, t);
	
	t = 1638929805;
	tm = localtime(&t);
	strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm);
	printf("now = %s, t = %ld\n", date, t);
}