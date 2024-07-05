#ifndef CHEEZEE_MOVELOGGER__
#define CHEEZEE_MOVELOGGER__

#include "board.h"
#include "cheezee.h"
#include "backend.h"
#include <ncurses.h>

typedef struct {
  size_t move;
  Board *board;
  WIN *log_win;
} Logger;

typedef struct {
  char *content;
  size_t size;
  size_t capacity;
} MoveString;

#define CREATE_STRING(str)                                                                                  \
  do {                                                                                                      \
    str = malloc(sizeof(MoveString));                                                                       \
    (str)->size = 1;                                                                                        \
    (str)->capacity = 1;                                                                                    \
    (str)->content = calloc((str)->capacity, sizeof(char));                                                 \
    (str)->content[0] = '\0';                                                                               \
  } while(0)

#define STRING_APPEND(str, val)                                                                             \
  do {                                                                                                      \
    if ((str)->size + 1 >= (str)->capacity) {                                                               \
      (str)->capacity *= 2;                                                                                 \
      (str)->content = realloc((str)->content, (str)->capacity * sizeof(char));                             \
    }                                                                                                       \
    (str)->content[(str)->size - 1] = val;                                                                  \
    (str)->content[(str)->size] = '\0';                                                                     \
    (str)->size++;                                                                                          \
  } while(0)

#define DESTROY_STRING(str)                                                                                 \
  do {                                                                                                      \
    free((str)->content);                                                                                   \
    free(str);                                                                                              \
    str = NULL;                                                                                             \
  } while(0)


Logger *create_logger(Board *board, WIN *log_win);
void log_move(Logger *logger, int srow, int scol, int erow, int ecol);
MoveString *translate_move(Logger *logger, int srow, int scol, int erow, int ecol);

#endif // CHEEZEE_MOVELOGGER__
