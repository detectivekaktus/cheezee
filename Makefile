CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb

all:
	$(CC) $(CFLAGS) -o main src/main.c
