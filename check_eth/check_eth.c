#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ETH_DEV_PATH	"/proc/net/dev"
#define ETH_NAME		"enp0s3"
#define UDISK_MNT_DIR  "/mdia/udisk-sda1"

int main(void)
{
	FILE *fp;
	char buf[2048];
	int ret;

	fp = fopen(ETH_DEV_PATH, "r");
	if (fp == NULL) {
		printf("open %s failure!\n", ETH_DEV_PATH);
		return -1;
	}
	
	memset(buf, 0, sizeof(buf));
	ret = fread(buf, 1, sizeof(buf)-1, fp);
	if (ret == 0) {
		printf("read %s failure!\n", ETH_DEV_PATH);
		return -1;
	} else {
		printf("read: \n%s\n", buf);
	}

	if (strstr(buf, ETH_NAME) != NULL)
		printf("eth check ok, name = %s\n", ETH_NAME);
	else
		printf("eth check failure, name = %s\n", ETH_NAME);
	
	if (access(UDISK_MNT_DIR, F_OK) == 0) {
		printf("udisk check ok\n");
	} else {
		printf("udisk check failure\n");
	}

	if (fp != NULL)
		fclose(fp);

	return 0;
}
