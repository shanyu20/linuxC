#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct foobar {
	int len;
	char value[0];
} foobar_t;

int main(int argc, char *argv[])
{
	printf("sizeof(int)=%d, sizeof(foobar_t)=%d\n",
			sizeof(int), sizeof(foobar_t));

	int *values = NULL;
	int i, j, *ptr;
	values = (int *)malloc(10*sizeof(int));
	if (NULL == values)
		return -1;

	for (i=0; i<10; i++)
		values[i] = 10 * (i+1);
	for (i=0; i<10; i++)
		printf(" %d", values[i]);
	printf("\n");

	foobar_t *buff = (foobar_t *)malloc(sizeof(foobar_t) + 10 * sizeof(int));
	buff->len = 10;
	memcpy(buff->value, values, 10 * sizeof(int));
	ptr = (int *)buff->value;
	printf("buff len = %d\n", buff->len);
	for (i=0; i<10; i++)
		printf("%d ", ptr[i]);
	printf("\n");
	free(buff);

	#define FOOBAR_T_SIZE(elements) (sizeof(foobar_t) + sizeof(int) * (elements))
	foobar_t *buf = (foobar_t *)malloc(6 * FOOBAR_T_SIZE(10));
	if (NULL == buf)
		return -1;
	memset(buf, 0, 6*FOOBAR_T_SIZE(10));

	foobar_t *ptr_buf;
	for (i=0; i<6; i++) {
		ptr_buf = (foobar_t *)((char *)buf + i*FOOBAR_T_SIZE(10));
		ptr_buf->len = i;
		memcpy(ptr_buf->value, values, i*sizeof(int));

		ptr = (int *)ptr_buf->value;
		printf("length: %d, values:", ptr_buf->len);
		for (j=0; j<10; j++)
			printf(" %d", ptr[j]);
		printf("\n");
	}
	free(buf);
	free(values);

	return 0;
}

