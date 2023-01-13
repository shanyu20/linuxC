TARGET=tcpClient
CFLAGS=-I/usr/local/include
LDFLAGS=-L/usr/local/lib -levent

$(TARGET): tcpClient.c
	gcc -o $@ $^ -levent
	
.PHONY: clean
clean:
	rm *.o $(TARGET)
