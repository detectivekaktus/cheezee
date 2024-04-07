CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb
TARGETS = main.o frontend.o
SOURCE = src/main.c src/frontend.c
WIN_LIBS = -I./include/win -L./include/win -lncurses -DNCURSES_STATIC
PSX_LIBS = -lncurses

win: win_targets
	$(CC) $(CFLAGS) -o main $(TARGETS) $(WIN_LIBS)

psx: psx_targets
	$(CC) $(CFLAGS) -o main $(TARGETS) $(PSX_LIBS)

win_targets: $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) $(WIN_LIBS)

psx_targets: $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) $(PSX_LIBS)
