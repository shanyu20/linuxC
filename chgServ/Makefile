#CC = gcc
CC = arm-linux-gcc
TARGET = chgServ
CFLAGS = -Werror -Wall
LDFLAGS = -lpthread
SRC = chgServ.c

$(TARGET): $(SRC) chgServ.h
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm *.o $(TARGET)
