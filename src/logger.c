#include "logger.h"
#include "backend.h"
#include "cheezee.h"

Logger *create_logger(Board *board, WIN *log_win) {
  Logger *logger = malloc(sizeof(Logger));
  logger->move = 0;
  logger->board = board;
  logger->log_win = log_win;
  return logger;
}

void log_move(Logger *logger, int srow, int scol, int erow, int ecol) {
  logger->move++;
  MoveString *str = translate_move(logger, srow, scol, erow, ecol);
  if (logger->move == 1) {
    mvwaddstr(logger->log_win->win, 2, 10, str->content);
    wrefresh(logger->log_win->win);
    DESTROY_STRING(str);
    return;
  }
  if (logger->move % 2 != 0) {
    mvwaddstr(logger->log_win->win, getcury(logger->log_win->win) + 2, 10, str->content);
  } else if (logger->move % 2 == 0) {
    mvwaddstr(logger->log_win->win, getcury(logger->log_win->win), getcurx(logger->log_win->win) + 5, str->content);
  } else if (logger->log_win->y - getcury(logger->log_win->win) <= 10) {
    wclear(logger->log_win->win);
    box(logger->log_win->win, 0, 0);
    mvwaddstr(logger->log_win->win, 2, 10, str->content);
  } else {
    mvwaddstr(logger->log_win->win, getcury(logger->log_win->win) + 2, 10, str->content);
  }
  wrefresh(logger->log_win->win);
  DESTROY_STRING(str);
}

MoveString *translate_move(Logger *logger, int srow, int scol, int erow, int ecol) {
  MoveString *str;
  CREATE_STRING(str);

  if (logger->board->current[srow][scol] != PAWN && logger->board->current[srow][scol] != PAWN + BLACK) {
    switch (logger->board->current[srow][scol]) {
      case KNIGHT: {
        STRING_APPEND(str, 'N');
        break;
      }
      case KNIGHT + BLACK: {
        STRING_APPEND(str, 'n');
        break;
      }
      case BISHOP: {
        STRING_APPEND(str, 'B');
        break;
      }
      case BISHOP + BLACK: {
        STRING_APPEND(str, 'b');
        break;
      }
      case ROOK: {
        STRING_APPEND(str, 'R');
        break;
      }
      case ROOK + BLACK: {
        STRING_APPEND(str, 'r');
        break;
      }
      case QUEEN: {
        STRING_APPEND(str, 'Q');
        break;
      }
      case QUEEN + BLACK: {
        STRING_APPEND(str, 'q');
        break;
      }
      case KING: {
        STRING_APPEND(str, 'K');
        break;
      }
      case KING + BLACK: {
        STRING_APPEND(str, 'k');
        break;
      }
      default: {
        CRASH("Unknown piece to be logged %d.", logger->board->current[srow][scol]);
      }
    }
  }
  if (!is_empty(logger->board->current[erow][ecol]) &&
    (logger->board->current[srow][scol] == PAWN || logger->board->current[srow][scol] == PAWN + BLACK)) {
    STRING_APPEND(str, 'a' + scol);
    STRING_APPEND(str, 'x');
  } else if (!is_empty(logger->board->current[erow][ecol])) STRING_APPEND(str, 'x');
  STRING_APPEND(str, 'a' + ecol);
  STRING_APPEND(str, '8' - erow);

  return str;
}
