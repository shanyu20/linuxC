#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

//#define SERV_IP_PORT		21306
#define RECV_MAX_LEN		1024
#define SEND_MAX_LEN		1024
#define WAIT_RECV_MAX_MS	3000

#define	SEND_MSG_STR	"hello client\n"

static int printUsage(char *cmd)
{
	printf("Usage: %s serv_port\n", cmd);

	return 0;
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serv_addr;
	char recv_buf[RECV_MAX_LEN] = {0};
	int recv_len = 0;
	char send_buf[RECV_MAX_LEN] = {0};
	int send_len = 0;
	struct sockaddr_in cli_addr;
	int addr_len;
	fd_set fdset;
	struct timeval tv;
	int ret;

	if (argc < 2) {
		printUsage(argv[0]);
		return -1;
	}
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("create socket failure");
		return -1;
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr = inet_addr("192.168.128.71");
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("bind failure");
		return -1;
	}

	while(1) {
		memset(recv_buf, 0, sizeof(recv_buf));
		recv_len = 0;
		memset(&cli_addr, 0, sizeof(cli_addr));
		addr_len = sizeof(cli_addr);

		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
		tv.tv_sec = WAIT_RECV_MAX_MS / 1000;
		tv.tv_usec = (WAIT_RECV_MAX_MS % 1000) * 1000;
		ret = select(sockfd+1, &fdset, NULL, NULL, &tv);
		if (ret > 0) {
			if (FD_ISSET(sockfd, &fdset)) {
				recv_len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), MSG_DONTWAIT, 
							(struct sockaddr *)&cli_addr, &addr_len);	//非阻塞
			}
		} else if (ret == 0) {
			printf("receive time out\n");
		} else {
			perror("select error");
		}
		if (recv_len > 0) {
			printf("recv from %s:%d len = %d: %s\n", inet_ntoa(cli_addr.sin_addr),
					ntohs(cli_addr.sin_port), recv_len, recv_buf);
#if 0
		cli_addr.sin_family = AF_INET;
		cli_addr.sin_addr.s_addr = inet_addr("192.168.128.111");
		cli_addr.sin_port = htons(8800);
#endif
			send_len = snprintf(send_buf, sizeof(send_buf), "server reply: %s\n", recv_buf);
			if (sendto(sockfd, send_buf, send_len, 0,
						(struct sockaddr *)&cli_addr, sizeof(cli_addr)) < 0)
				perror("send failure");
		}
	}
	close(sockfd);
	return 0;
}
