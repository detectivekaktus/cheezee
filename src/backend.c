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
        if (is_empty(cur_board[row][col])) break;
        Moves *moves = get_moves(cur_board, row, col);
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

Moves *get_moves(int **board, const int row, const int col) {
  switch (board[row][col]) {
    case PAWN + BLACK:
    case PAWN: {
      return get_pawn_moves(board, row, col);
    }
    case KNIGHT + BLACK:
    case KNIGHT: {
      return get_knight_moves(board, row, col);
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
      return get_queen_moves(board, row, col);
    }
    case KING + BLACK:
    case KING: {
      return get_king_moves(board, row, col);
    }
    default: {
      CRASH("unexpected piece found. piece: %d", board[row][col]);
    }
  }
}

// TODO (#1): Add the en-passant move.
Moves *get_pawn_moves(int **board, int row, int col) {
  Moves *moves;
  MOVES_INIT(moves);

  if (is_white_piece(board[row][col])) {
    if (is_in_board_limit(row - 1) && (is_in_board_limit(col - 1) || is_in_board_limit(col + 1))) {
      if (is_in_board_limit(col - 1) && !is_empty(board[row - 1][col - 1]) && !is_white_piece(board[row - 1][col - 1])) MOVES_ADD(moves, row - 1, col - 1);
      if (is_in_board_limit(col + 1) && !is_empty(board[row - 1][col + 1]) && !is_white_piece(board[row - 1][col + 1])) MOVES_ADD(moves, row - 1, col + 1);
    }

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
    if (is_in_board_limit(row + 1) && (is_in_board_limit(col - 1) || is_in_board_limit(col + 1))) {
      if (is_in_board_limit(col - 1) && !is_empty(board[row + 1][col - 1]) && is_white_piece(board[row + 1][col - 1])) MOVES_ADD(moves, row + 1, col - 1);
      if (is_in_board_limit(col + 1) && !is_empty(board[row + 1][col + 1]) && is_white_piece(board[row + 1][col + 1])) MOVES_ADD(moves, row + 1, col + 1);
    }

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

Moves *get_knight_moves(int **board, int row, int col) {
  const bool is_white = is_white_piece(board[row][col]);
  Moves *moves;
  MOVES_INIT(moves);

  const int y[] = { -2, -1, 1, 2 };
  const int x[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
  int i = 0;
  int j = 0;
  while (j < 8) {
    const int end_row = row + y[i];
    const int end_col = col + x[j];
    if (is_in_board_limit(end_row) && is_in_board_limit(end_col)) {
      if (is_empty(board[end_row][end_col]) || is_white != is_white_piece(board[end_row][end_col])) MOVES_ADD(moves, end_row, end_col);
    }
    i += (j % 2 != 0) ? 1 : 0;
    j++;
  }

  return moves;
}

Moves *get_bishop_moves(int **board, int row, int col) {
  const bool is_white = is_white_piece(board[row][col]);
  Moves *moves;
  MOVES_INIT(moves);

  traverse_diagonal(moves, board, is_in_board_limit(row + 1) ? row + 1 : row, is_in_board_limit(col + 1) ? col + 1 : col, 1, 1, is_white);
  traverse_diagonal(moves, board, is_in_board_limit(row - 1) ? row - 1 : row, is_in_board_limit(col - 1) ? col - 1 : col, -1, -1, is_white);
  traverse_diagonal(moves, board, is_in_board_limit(row + 1) ? row + 1 : row, is_in_board_limit(col - 1) ? col - 1 : col, 1, -1, is_white);
  traverse_diagonal(moves, board, is_in_board_limit(row - 1) ? row - 1 : row, is_in_board_limit(col + 1) ? col + 1 : col, -1, 1, is_white);

  return moves;
}

Moves *get_rook_moves(int **board, int row, int col) {
  const bool is_white = is_white_piece(board[row][col]);
  Moves *moves;
  MOVES_INIT(moves);

  traverse_vertical(moves, board, is_in_board_limit(row + 1) ? row + 1 : row, col, 1, is_white);
  traverse_vertical(moves, board, is_in_board_limit(row - 1) ? row - 1 : row, col, -1, is_white);
  traverse_horizontal(moves, board, row, is_in_board_limit(col + 1) ? col + 1 : col, 1, is_white);
  traverse_horizontal(moves, board, row, is_in_board_limit(col - 1) ? col - 1 : col, -1, is_white);

  return moves;
}

Moves *get_queen_moves(int **board, int row, int col) {
  const bool is_white = is_white_piece(board[row][col]);
  Moves *moves;
  MOVES_INIT(moves);

  traverse_vertical(moves, board, is_in_board_limit(row + 1) ? row + 1 : row, col, 1, is_white);
  traverse_vertical(moves, board, is_in_board_limit(row - 1) ? row - 1 : row, col, -1, is_white);
  traverse_horizontal(moves, board, row, is_in_board_limit(col + 1) ? col + 1 : col, 1, is_white);
  traverse_horizontal(moves, board, row, is_in_board_limit(col - 1) ? col - 1 : col, -1, is_white);

  traverse_diagonal(moves, board, is_in_board_limit(row + 1) ? row + 1 : row, is_in_board_limit(col + 1) ? col + 1 : col, 1, 1, is_white);
  traverse_diagonal(moves, board, is_in_board_limit(row - 1) ? row - 1 : row, is_in_board_limit(col - 1) ? col - 1 : col, -1, -1, is_white);
  traverse_diagonal(moves, board, is_in_board_limit(row + 1) ? row + 1 : row, is_in_board_limit(col - 1) ? col - 1 : col, 1, -1, is_white);
  traverse_diagonal(moves, board, is_in_board_limit(row - 1) ? row - 1 : row, is_in_board_limit(col + 1) ? col + 1 : col, -1, 1, is_white);

  return moves;
}

// TODO (#2): Check if the attacked piece has a defender.
// TODO (#3): Add casteling move.
Moves *get_king_moves(int **board, int row, int col) {
  const bool is_white = is_white_piece(board[row][col]);
  Moves *moves;
  MOVES_INIT(moves);

  const int y[] = { 0, 1, -1 };
  const int x[] = { 0, 1, -1 };
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (y[i] == 0 && x[j] == 0) continue;
      const int end_row = row + y[i];
      const int end_col = col + x[j];
      if (is_in_board_limit(end_row) && is_in_board_limit(end_col)) {
        if (is_empty(board[end_row][end_col])) MOVES_ADD(moves, end_row, end_col);
        if (is_white != is_white_piece(board[end_row][end_col])) MOVES_ADD(moves, end_row, end_col);
      }
    }
  }

  return moves;
}

void traverse_diagonal(Moves *moves, int **board, int row, int col, int inc_y, int inc_x, const bool is_white) {
  while (is_in_board_limit(row) && is_in_board_limit(col)) {
    if (!is_empty(board[row][col])) {
      if (is_white == is_white_piece(board[row][col])) {
        break;
      } else {
        MOVES_ADD(moves, row, col);
        break;
      }
    }
    MOVES_ADD(moves, row, col);
    row += inc_y;
    col += inc_x;
  }
}

void traverse_vertical(Moves *moves, int **board, int row, int col, int inc, const bool is_white) {
  while (is_in_board_limit(row) && is_in_board_limit(col)) {
    if (!is_empty(board[row][col])) {
      if (is_white == is_white_piece(board[row][col])) {
        break;
      } else {
        MOVES_ADD(moves, row, col);
        break;
      }
    }
    MOVES_ADD(moves, row, col);
    row += inc;
  }
}

void traverse_horizontal(Moves *moves, int **board, int row, int col, int inc, const bool is_white) {
  while (is_in_board_limit(row) && is_in_board_limit(col)) {
    if (!is_empty(board[row][col])) {
      if (is_white == is_white_piece(board[row][col])) {
        break;
      } else {
        MOVES_ADD(moves, row, col);
        break;
      }
    }
    MOVES_ADD(moves, row, col);
    col += inc;
  }
}

bool is_in_board_limit(const int axis) {
  return (axis <= 7) && (axis >= 0);
}

bool can_move(const Moves *moves) {
  return moves->size != 0;
}

bool is_white_piece(const int piece) {
  return piece - BLACK != abs(piece - BLACK);
}

bool is_empty(const int tile) {
  return tile == 0;
}
