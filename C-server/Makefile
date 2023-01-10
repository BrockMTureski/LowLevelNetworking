
CC=gcc
CFLAGS=-g
COMMON_OBJS = common.o

all: $(COMMON_OBJS) tcpc

common.o: common.h common.c
	$(CC) $(CFLAGS) -c common.c

tcpc: Client.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcpc Client.c $(COMMON_OBJS)

clean:
	rm -rf *.o *.dSYM tcpc