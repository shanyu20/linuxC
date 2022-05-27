TARGET=upfile
CFLAGS=-I/usr/local/include
LDFLAGS=-L/usr/lib -lcurl
CC=gcc

$(TARGET): upfile.c
	$(CC) -o $@ $^ -lcurl

.PHONY:clean
clean:
	rm *.o $(TARGET)