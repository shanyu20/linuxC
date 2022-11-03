#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/time.h>

#define SERVER_IP	"192.168.1.11"
#define SERVER_PORT	8888

char send_buf[1024] = {0};
int send_idx = 0;
int send_len = 0;
int count = 0;

int wait_server_data(int sock_fd)
{
	char recv_buf[256] = {0};
	int recv_len = 0;
	fd_set rdset, wrset;
	struct timeval timeout;
	int ret = 0;
	
	if (sock_fd < 0)
		return -1;
	FD_ZERO(&rdset);
	FD_ZERO(&wrset);
	FD_SET(sock_fd, &rdset);
	if (send_len > 0)
		FD_SET(sock_fd, &wrset);
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	ret = select(sock_fd + 1, &rdset, &wrset, NULL, &timeout);
	if (ret > 0) {
		if (FD_ISSET(sock_fd, &rdset)) {
			recv_len = recv(sock_fd, recv_buf, sizeof(recv_buf) - 1, MSG_DONTWAIT);
			if (recv_len > 0) {
				memcpy(send_buf + send_idx + send_len, recv_buf, recv_len);
				send_len += recv_len;
				printf("recv: len = %d\n%s\n", recv_len, recv_buf);
				ret = 0;
			} else {
				perror("recv error");
				ret = -1;
			}
		}
		if (FD_ISSET(sock_fd, &wrset)) {
			if (send_len > 0) {
				int len = 0;
				count++;
				len = send(sock_fd, send_buf + send_idx, send_len, MSG_DONTWAIT);
				printf("send count = %d, len = %d\n", count, len);
				if (len == send_len) {
					send_idx = 0;
					send_len = 0;
					memset(send_buf, 0, sizeof(send_buf));
				} else if (len > 0) {
					send_idx += len;
					send_len -= len;
				}
			}
		}
	} else if (ret == 0) {
		printf("select time out\n");
		ret = -1;
	} else {
		printf("select error\n");
	}
	
	return ret;
}

int main(void)
{
	struct sockaddr_in server;
	int sock_fd;
	int ret = 0;
	
	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		perror("create socket failure");
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	ret = connect(sock_fd, (const struct sockaddr *)&server, sizeof(struct sockaddr_in));
	if (ret == -1) {
		perror("connect failure");
		return -1;
	}
	while (1) {
		wait_server_data(sock_fd);
		sleep(1);
	}
	close(sock_fd);
	
	return 0;
}
