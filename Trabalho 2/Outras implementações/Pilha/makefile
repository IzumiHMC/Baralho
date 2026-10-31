CC = gcc
CFLAGS = -Wall -Wextra -O2
SRCS = $(wildcard ./codigos/*.c)

all: ex

ex: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o ./ex
	$(CC) $(CFLAGS) ./gerador.c -o ./ger

clean: 
	rm -f *.o ex

.PHONY: clean ex