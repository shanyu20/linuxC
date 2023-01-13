TARGETS:=ntyreactor
CC=gcc

NTY_SRCS:=ntyreactor.c

.PHONY: all clean distclean

all: $(TARGETS)

ntyreactor: $(NTY_SRCS)
	$(CC) $(NTY_SRCS) -o $@

clean:
	rm -rf *.o

distclean: clean
	rm -rf $(TARGETS)
