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

Logger *create_logger(Board *board, WIN *log_win);
void log_move(Logger *logger, int srow, int scol, int erow, int ecol);
String *translate_move(Logger *logger, int srow, int scol, int erow, int ecol);

#endif // CHEEZEE_MOVELOGGER__
