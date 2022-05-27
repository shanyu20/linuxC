#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE *fp;
	char buffer[256];
	int i = 0;
	
	fp = popen("cat /etc/passwd", "r");
	while (1) {
		
		memset(buffer, 0, sizeof(buffer));
		if (fgets(buffer, sizeof(buffer), fp) == NULL)
			break;
		printf("count = %d : %s", i++, buffer);
	}
	pclose(fp);
}
