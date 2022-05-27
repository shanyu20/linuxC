#include <stdio.h>

#define YES		"Hello, world!"

int main(int argc, char *argv[])
{
	printf("output1: YES\n");
	printf("output2:"YES"\n");
	printf("output3:" YES "\n");
	
#ifdef MY_NAME
	printf("my name is \"" MY_NAME "\"\n");
#endif
	return 0;
}
