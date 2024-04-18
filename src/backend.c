#include "cheezee.h"
#include "backend.h"
#include "frontend.h"

void play(Program *program) {
  WIN *help;
  WIN *help_text;
  WIN *log;
  WIN *log_text;

  CREATE_WINDOW(help, ceil(program->y * 0.4), program->x - (TILE_WIDTH * 8 + 2), program->y - (program->y * 0.4), TILE_WIDTH * 8 + 2);
  CREATE_WINDOW(help_text, help->y * 0.8, help->x * 0.8, help->start_y + 2, help->start_x + 5);
  wattron(help_text->win, A_REVERSE);
  wprintw(help_text->win, "\u2190 \u2191 \u2192 \u2193");
  wattroff(help_text->win, A_REVERSE);
  wprintw(help_text->win, " move around the board\n\n");
  wattron(help_text->win, A_REVERSE);
  wprintw(help_text->win, "Enter");
  wattroff(help_text->win, A_REVERSE);
  wprintw(help_text->win, " select and submit an action");
  box(help->win, 0, 0);
  wrefresh(help->win);
  wrefresh(help_text->win);

  CREATE_WINDOW(log, program->y * 0.6, program->x - (TILE_WIDTH * 8 + 2), 0, TILE_WIDTH * 8 + 2);
  CREATE_WINDOW(log_text, log->y * 0.8, log->x * 0.8, log->start_x + 5, log->start_y + 5);
  mvwprintw(log->win, 1, 5, "Moves log");
  box(log->win, 0, 0);
  wrefresh(log->win);
  wrefresh(log_text->win);

  int **cur_board = start_standard_board();
  int **prev_board = start_standard_board();
  int row = 0;
  int col = 0;
  int input;

  draw_board(program);
  draw_pieces(program, cur_board);
  highlight_tile(program, row, col);
  keypad(program->board->win, true);
  do {
    input = wgetch(program->board->win);
    switch (input) {
      case KEY_UP: {
        if (row > 0) {
          draw_tile_row_col(program, row, col, is_white_tile(row, col) ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          row--;
          highlight_tile(program, row, col);
        }
        break;
      }
      case KEY_DOWN: {
        if (row < 7) {
          draw_tile_row_col(program, row, col, is_white_tile(row, col) ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          row++;
          highlight_tile(program, row, col);
        }
        break;
      }
      case KEY_LEFT: {
        if (col > 0) {
          draw_tile_row_col(program, row, col, is_white_tile(row, col) ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          col--;
          highlight_tile(program, row, col);
        }
        break;
      }
      case KEY_RIGHT: {
        if (col < 7) {
          draw_tile_row_col(program, row, col, is_white_tile(row, col) ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          col++;
          highlight_tile(program, row, col);
        }
        break;
      }
      case ENTER: {
        if (cur_board[row][col] == 0) break;
        Moves *moves = get_available_moves(cur_board, row, col);
        if (!can_move(moves)) {
          MOVES_DESTROY(moves);
          break;
        }
        for (size_t i = 0; i < moves->size; i++) {
          for (int j = 0; j < 2; j++) {
            printf("%d\n", moves->moves[i][j]);
          }
        }
        printf("%zu %zu\n", moves->capacity, moves->size);
        CRASH("\n");
      }
      default: {
        break;
      }
    }
  } while (input != 'Q' && input != 'q');
  DESTROY_WINDOW(help);
  DESTROY_WINDOW(help_text);
  DESTROY_WINDOW(log);
  DESTROY_WINDOW(log_text);
  DESTROY_WINDOW(program->board);
  for (int i = 0; i < 8; i++) {
    free(cur_board[i]);
    free(prev_board[i]);
  }
  free(cur_board);
  free(prev_board);
}

int **start_standard_board() {
  int **board = calloc(8, sizeof(int *));
  if (board == NULL) CRASH("buy more RAM lol");
  for (int i = 0; i < 8; i++) {
    board[i] = calloc(8, sizeof(int));
    if (board[i] == NULL) CRASH("buy more RAM lol");
  }
  board[0][0] = BLACK + ROOK;
  board[0][1] = BLACK + KNIGHT;
  board[0][2] = BLACK + BISHOP;
  board[0][3] = BLACK + QUEEN;
  board[0][4] = BLACK + KING;
  board[0][5] = BLACK + BISHOP;
  board[0][6] = BLACK + KNIGHT;
  board[0][7] = BLACK + ROOK;
  for (int i = 0; i < 8; i++) board[1][i] = BLACK + PAWN;

  for (int i = 0; i < 8; i++) board[6][i] = WHITE + PAWN;
  board[7][0] = WHITE + ROOK;
  board[7][1] = WHITE + KNIGHT;
  board[7][2] = WHITE + BISHOP;
  board[7][3] = WHITE + QUEEN;
  board[7][4] = WHITE + KING;
  board[7][5] = WHITE + BISHOP;
  board[7][6] = WHITE + KNIGHT;
  board[7][7] = WHITE + ROOK;
  return board;
}

Moves *get_available_moves(int **board, const int row, const int col) {
  switch (board[row][col]) {
    case PAWN + BLACK:
    case PAWN: {
      return get_pawn_moves(board, row, col);
    }
    case KNIGHT + BLACK:
    case KNIGHT: {
      ASSERT(false, "not implemented\n");
    }
    case BISHOP + BLACK:
    case BISHOP: {
      return get_bishop_moves(board, row, col);
    }
    case ROOK + BLACK:
    case ROOK: {
      return get_rook_moves(board, row, col);
    }
    case QUEEN + BLACK:
    case QUEEN: {
      ASSERT(false, "not implemented\n");
    }
    case KING + BLACK:
    case KING: {
      ASSERT(false, "not implemented\n");
    }
    default: {
      CRASH("unexpected piece found. piece: %d", board[row][col]);
    }
  }
}

Moves *get_pawn_moves(int **board, int row, int col) {
  Moves *moves;
  MOVES_INIT(moves);

  if (is_white_piece(board[row][col])) {
    if (row == 6) {
      row--;
      int i = 0;
      while (is_empty(board[row][col]) && i < 2) {
        MOVES_ADD(moves, row, col);
        row--;
        i++;
      }
    } else {
      row--;
      if (is_empty(board[row][col])) MOVES_ADD(moves, row, col);
    }
  } else {
    if (row == 1) {
      row++;
      int i = 0;
      while (is_empty(board[row][col]) && i < 2) {
        MOVES_ADD(moves, row, col);
        row++;
        i++;
      }
    } else {
      row++;
      if (is_empty(board[row][col])) MOVES_ADD(moves, row, col);
    }
  }

  return moves;
}

Moves *get_bishop_moves(int **board, int row, int col) {
  Moves *moves;
  int iter_row, iter_col;
  MOVES_INIT(moves);

  iter_row = is_in_board_limit(row + 1) ? row + 1 : row;
  iter_col = is_in_board_limit(col + 1) ? col + 1 : col;
  traverse_diagonal(moves, board, iter_row, iter_col, 1, 1);

  iter_row = is_in_board_limit(row - 1) ? row - 1 : row;
  iter_col = is_in_board_limit(col - 1) ? col - 1 : col;
  traverse_diagonal(moves, board, iter_row, iter_col, -1, -1);

  iter_row = is_in_board_limit(row + 1) ? row + 1 : row;
  iter_col = is_in_board_limit(col - 1) ? col - 1 : col;
  traverse_diagonal(moves, board, iter_row, iter_col, 1, -1);

  iter_row = is_in_board_limit(row - 1) ? row - 1 : row;
  iter_col = is_in_board_limit(col + 1) ? col + 1 : col;
  traverse_diagonal(moves, board, iter_row, iter_col, -1, 1);

  return moves;
}

Moves *get_rook_moves(int **board, int row, int col) {
  Moves *moves;
  int iter_row, iter_col;
  MOVES_INIT(moves);

  iter_row = is_in_board_limit(row + 1) ? row + 1 : row;
  iter_col = col;
  traverse_vertical(moves, board, iter_row, iter_col, 1);

  iter_row = is_in_board_limit(row - 1) ? row - 1 : row;
  iter_col = col;
  traverse_vertical(moves, board, row, col, -1);

  iter_row = row;
  iter_col = is_in_board_limit(col + 1) ? col + 1 : col;
  traverse_horizontal(moves, board, iter_row, iter_col, 1);

  iter_row = row;
  iter_col = is_in_board_limit(col - 1) ? col - 1 : col;
  traverse_horizontal(moves, board, iter_row, iter_col, -1);

  return moves;
}

void traverse_diagonal(Moves *moves, int **board, int row, int col, int inc_y, int inc_x) {
  while (is_empty(board[row][col]) && (is_in_board_limit(row) && is_in_board_limit(col))) {
    MOVES_ADD(moves, row, col);
    row += inc_y;
    col += inc_x;
  }
}

void traverse_vertical(Moves *moves, int **board, int row, int col, int inc) {
  while (is_empty(board[row][col]) && (is_in_board_limit(row) && is_in_board_limit(col))) {
    MOVES_ADD(moves, row, col);
    row += inc;
  }
}

void traverse_horizontal(Moves *moves, int **board, int row, int col, int inc) {
  while (is_empty(board[row][col]) && (is_in_board_limit(row) && is_in_board_limit(col))) {
    MOVES_ADD(moves, row, col);
    col += inc;
  }
}

bool is_in_board_limit(const int axis) {
  return (axis <= 7) && (axis >= 0);
}

bool can_move(Moves *moves) {
  return moves->size != 0;
}

bool is_white_piece(const int piece) {
  return piece - BLACK != abs(piece - BLACK);
}

bool is_empty(const int tile) {
  return tile == 0;
}
