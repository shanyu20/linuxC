TARGET=client

$(TARGET): client.c
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
