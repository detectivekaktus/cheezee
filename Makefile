CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb
TARGETS = main.o frontend.o backend.o
SOURCE = src/main.c src/frontend.c src/backend.c
WIN_LIBS = -I./include/win -L./include/win -lncurses -DNCURSES_STATIC
PSX_LIBS = -lncurses -lm

win: win_targets
	$(CC) $(CFLAGS) -o main $(TARGETS) $(WIN_LIBS)

psx: psx_targets
	$(CC) $(CFLAGS) -o main $(TARGETS) $(PSX_LIBS)

win_targets: $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) $(WIN_LIBS)

psx_targets: $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) $(PSX_LIBS)
