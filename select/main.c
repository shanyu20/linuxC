#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	fd_set read_set;
	struct timeval timeout;
	char read_buf[5] = {0};
	int ret = 0;

	while(1) {
		timeout.tv_sec = 30;
		timeout.tv_usec = 0;
		FD_ZERO(&read_set);
		FD_SET(STDIN_FILENO, &read_set);
		ret = select(STDIN_FILENO + 1, &read_set, NULL, NULL, &timeout);
		if (ret > 0) {
			if (FD_ISSET(STDIN_FILENO, &read_set)) {
				memset(read_buf, 0, sizeof(read_buf));
				fgets(read_buf, sizeof(read_buf), stdin);
				printf("rest time: sec=%ld, usec=%ld\n", timeout.tv_sec, timeout.tv_usec);
				printf("read %ld bytes: %s\n", strlen(read_buf), read_buf);
			}
		} else if (ret == 0) {
			printf("it is timeout\n");
		} else {
			printf("select error\n");
		}
	}
	
	return 0;
}
