#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int flags, opt;
	int nsecs, tfnd;

	nsecs = 0;
	tfnd = 0;
	flags = 0;
	for (int i = 0; i < argc; i++) {
		printf("argv[%d]=%s; ", i, argv[i]);
	}
	putchar('\n');
	while ((opt = getopt(argc, argv, "nt:")) != -1) {
		switch (opt) {
			case 'n':
				flags = 1;
				break;
			case 't':
				nsecs = atoi(optarg);
				tfnd = 1;
				break;
			default: //'?'
				fprintf(stderr, "optopt=%c\n", (char)optopt);
				fprintf(stderr, "opterr=%d\n", opterr);
				fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	
	printf("flags=%d; tfnd=%d; optind=%d; nsecs=%d\n", flags, tfnd, optind, nsecs);
	printf("optind=%d, argc=%d\n", optind, argc);
	if (optind >= argc) {
		fprintf(stderr, "Expected argument after options\n");
		exit(EXIT_FAILURE);
	}

	printf("name argument = %s\n", argv[optind]);

	exit(EXIT_SUCCESS);
}
