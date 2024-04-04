CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb

win:
	$(CC) $(CFLAGS) -o main src/main.c -I./include/win -L./include/win -lncurses -DNCURSES_STATIC

psx:
	$(CC) $(CFLAGS) -o main src/main.c -lncurses
