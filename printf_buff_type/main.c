#include <stdio.h>

void print_info(FILE *f)
{
	if (f->_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else if (f->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");

	printf("    buffer size: %d\n", f->_IO_buf_end - f->_IO_buf_base);
	printf("    discriptor: %d\n\n", fileno(f));
}

int main(void)
{
	printf("stdin is ");
	print_info(stdin);

	printf("stdout is ");
	print_info(stdout);

	printf("stderr is ");
	print_info(stderr);

	return 0;
}
