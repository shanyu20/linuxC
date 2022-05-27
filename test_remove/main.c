#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	if (remove("./aa.txt") != 0) {
		printf("remove aa.txt failure!, errno = %d\n", errno);
	} else {
		printf("remove aa.txt success!\n");
	}

	if (unlink("./bb.txt") != 0) {
		printf("unlink bb.txt failure!, errno = %d\n", errno);
	} else {
		printf("unlink bb.txt success!\n");
	}
	
	return 0;
}
