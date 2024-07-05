CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ggdb
TARGETS = main.o frontend.o backend.o board.o logger.o
SOURCE = src/main.c src/frontend.c src/backend.c src/board.c src/logger.c
LIBS = -lncursesw -lm

all: $(TARGETS)
	$(CC) $(CFLAGS) -o cheezee $(TARGETS) $(LIBS)

$(TARGETS):
	$(CC) $(CFLAGS) -c $(SOURCE) $(LIBS)

rebuild: clean all
	./cheezee

clean:
	rm *.o
	rm cheezee
