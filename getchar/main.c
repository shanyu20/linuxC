#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define MAX_BUF_LEN		128

int main(void)
{
	char c;
	char buf[MAX_BUF_LEN] = {0};
	int i = 0;
	struct termios oldt, newt;
	
	tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
 
	printf("Please input:\n");
	while((c = getchar()) != '\n' && i < MAX_BUF_LEN - 1) {
		if (c == '\b') {
			if (i > 0) {
				putchar('\b');
				putchar(' ');
				putchar('\b');
				buf[--i] = '\0';
			}
			else {
				buf[0] = '\0';
			}
		} else {
			putchar(c);
			buf[i++] = c;
		}
	}
	buf[i] = '\0';
	putchar(c);

	printf("input string is: %s\n", buf);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
