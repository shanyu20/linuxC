#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define TEST_STR_1	"12"
#define TEST_STR_2	"AB"

int main(int argc, char *argv[])
{
	int fd1, fd2;
	int mode = 0;
	
	if (argc < 2) {
		printf("Usage:\n");
		printf("	%s mode\n", argv[0]);
		printf("	mode=0: no append\n");
		printf("	mode=1: append\n");
		return -1;
	}
	mode = atol(argv[1]);
	if (mode == 0)
		fd1 = open("test.txt", O_CREAT | O_RDWR | O_SYNC | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	else
		fd1 = open("test.txt", O_CREAT | O_RDWR | O_SYNC | O_APPEND | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd1 < 0) {
		perror("fd1: open failure");
		return -1;
	}
	if (mode == 0)
		fd2 = open("test.txt", O_CREAT | O_RDWR | O_SYNC | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	else
		fd2 = open("test.txt", O_CREAT | O_RDWR | O_SYNC | O_APPEND | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd2 < 0) {
		perror("fd2: open failure");
		return -1;
	}
	printf("open success: fd1 = %d, fd2 = %d\n", fd1, fd2);
	
	while (1) {
		int len = 0;
		char rdBuf[128] = {0};
		printf("write fd1: %s\n", TEST_STR_1);
		if (write(fd1, TEST_STR_1, strlen(TEST_STR_1)) < strlen(TEST_STR_1)) {
			perror("fd1 write failure");
			return -1;
		}
		lseek(fd1, 0, SEEK_SET);
		memset(rdBuf, 0, sizeof(rdBuf));
		len = read(fd1, rdBuf, sizeof(rdBuf));
		if (len < 0) {
			perror("fd1 read failure");
			return -1;
		}
		printf("read fd1: %s\n", rdBuf);
		
		printf("write fd2: %s\n", TEST_STR_2);
		if (write(fd2, TEST_STR_2, strlen(TEST_STR_2)) < strlen(TEST_STR_2)) {
			perror("fd2 write failure");
			return -1;
		}
		lseek(fd2, 0, SEEK_SET);
		memset(rdBuf, 0, sizeof(rdBuf));
		len = read(fd2, rdBuf, sizeof(rdBuf));
		if (len < 0) {
			perror("fd2 read failure");
			return -1;
		}
		printf("read fd2: %s\n", rdBuf);
		sleep(3);
	}
	close(fd1);
	close(fd2);
	
	return 0;
}