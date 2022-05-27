#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	fork();
	fork();
	fork();
	printf("Hello world!\n");
}
