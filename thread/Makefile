TARGET := thread

$(TARGET): create.c
	gcc -o $@ $^ -lpthread

.PHONIC: clean
clean:
	rm $@ *.o
