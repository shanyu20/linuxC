LDFLAGS := -lpthread

all: chat_serv chat_clnt

chat_serv: chat_serv.c
	gcc -o $@ $< -D_REENTRANT $(LDFLAGS)

chat_clnt: chat_clnt.c
	gcc -o $@ $< -D_REENTRANT $(LDFLAGS)

.PHONY: clean
clean:
	rm chat_serv chat_clnt *.o

