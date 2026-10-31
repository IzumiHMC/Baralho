CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -O2


PROGRAMA = deck

SRC_MAIN = main.c deque.c baralho.c
HEADERS  = $(wildcard *.h)

all: $(PROGRAMA) gerador

$(PROGRAMA): $(SRC_MAIN) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC_MAIN) -o $(PROGRAMA)

gerador: gerador.c
	$(CC) $(CFLAGS) gerador.c -o gerador

clean:
	rm -f $(PROGRAMA) gerador

.PHONY: all clean