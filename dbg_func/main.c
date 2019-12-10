#include <stdio.h>
#define DEBUG

#ifdef DEBUG
#define debug(fmt, args...) printf("debug: " fmt "\n", ##args)

#define debug2(fmt, ...) printf("debug2: " fmt "\n",## __VA_ARGS__)

#define debug3(...) do { printf("debug3: " __VA_ARGS__); putchar('\n');} while(0);

#define debug4(fmt, args...) do { printf("debug4: " fmt, ##args); putchar('\n');} while(0);
#else
#define debug(fmt, args...)
#define debug2(fmt, ...)
#define debug3(...)
#define debug4(fmt, ...)
#endif

int main(void)
{
	printf("test debug print\n");
	debug("Hello, world!");	
	debug2("Hello, world!");
	debug3("Hello, world!");
	debug4("Hello, world!");
	printf("test finish!\n");
}

