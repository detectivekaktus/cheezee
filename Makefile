CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb
TARGETS = main.o frontend.o backend.o
SOURCE = src/main.c src/frontend.c src/backend.c
LIBS = -lncursesw -lm

all: $(TARGETS)
	$(CC) $(CFLAGS) -o cheezee $(TARGETS) $(LIBS)

$(TARGETS):
	$(CC) $(CFLAGS) -c $(SOURCE) $(LIBS)

run: all
	./cheezee

clean:
	rm *.o
	rm cheezee
