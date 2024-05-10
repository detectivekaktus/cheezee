#include "cheezee.h"
#include "backend.h"
#include "frontend.h"
#include <stdio.h>

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

  int **cur_board = stdboard();
  int **prev_board = empty_board();
  bool is_white_turn = true;
  int row = 0;
  int col = 0;
  int input;

  draw_board(program);
  draw_pieces(program, cur_board);
  highlight_tile(program, row, col, SELECTION);
  keypad(program->board->win, true);
  do {
    input = wgetch(program->board->win);
    switch (input) {
      case KEY_UP:
      case 'k':
      case 'K': {
        if (row > 0) {
          draw_tile_row_col(program, row, col);
          draw_piece(program, row, col, cur_board[row][col]);
          row--;
          highlight_tile(program, row, col, SELECTION);
        }
        break;
      }
      case KEY_DOWN:
      case 'j':
      case 'J': {
        if (row < 7) {
          draw_tile_row_col(program, row, col);
          draw_piece(program, row, col, cur_board[row][col]);
          row++;
          highlight_tile(program, row, col, SELECTION);
        }
        break;
      }
      case KEY_LEFT:
      case 'h':
      case 'H': {
        if (col > 0) {
          draw_tile_row_col(program, row, col);
          draw_piece(program, row, col, cur_board[row][col]);
          col--;
          highlight_tile(program, row, col, SELECTION);
        }
        break;
      }
      case KEY_RIGHT:
      case 'l':
      case 'L': {
        if (col < 7) {
          draw_tile_row_col(program, row, col);
          draw_piece(program, row, col, cur_board[row][col]);
          col++;
          highlight_tile(program, row, col, SELECTION);
        }
        break;
      }
      case ENTER: {
        if (is_empty(cur_board[row][col])) break;
        int mrow = row;
        int mcol = col;
        do {
          input = wgetch(program->board->win);
          switch (input) {
            case KEY_UP:
            case 'k':
            case 'K': {
              if (mrow > 0) {
                draw_tile_row_col(program, mrow, mcol);
                draw_piece(program, mrow, mcol, cur_board[mrow][mcol]);
                mrow--;
                highlight_tile(program, mrow, mcol, SELECTION);
              }
              break;
            }
            case KEY_DOWN:
            case 'j':
            case 'J': {
              if (mrow < 7) {
                draw_tile_row_col(program, mrow, mcol);
                draw_piece(program, mrow, mcol, cur_board[mrow][mcol]);
                mrow++;
                highlight_tile(program, mrow, mcol, SELECTION);
              }
              break;
            }
            case KEY_LEFT:
            case 'h':
            case 'H': {
              if (mcol > 0) {
                draw_tile_row_col(program, mrow, mcol);
                draw_piece(program, mrow, mcol, cur_board[mrow][mcol]);
                mcol--;
                highlight_tile(program, mrow, mcol, SELECTION);
              }
              break;
            }
            case KEY_RIGHT:
            case 'l':
            case 'L': {
              if (mcol < 7) {
                draw_tile_row_col(program, mrow, mcol);
                draw_piece(program, mrow, mcol, cur_board[mrow][mcol]);
                mcol++;
                highlight_tile(program, mrow, mcol, SELECTION);
              }
              break;
            }
            default: {
              break;
            }
          }
        } while (input != ESCAPE && input != ENTER);
        if (input == ESCAPE ||
          ((mrow == row) && (mcol == col)) ||
          !is_legal_move(cur_board, prev_board, row, col, mrow, mcol)) break;
        play_move(cur_board, prev_board, row, col, mrow, mcol);
        update_board(program, cur_board, prev_board);
        draw_tile_row_col(program, mrow, mcol);
        draw_piece(program, mrow, mcol, cur_board[mrow][mcol]);
        highlight_tile(program, mrow, mcol, SELECTION);
        row = mrow;
        col = mcol;
        is_white_turn = !is_white_turn;
        break;
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
  free_board(cur_board);
  free_board(prev_board);
}

int **empty_board() {
  int **board = calloc(8, sizeof(int *));
  if (board == NULL) CRASH("buy more RAM lol");
  for (int i = 0; i < 8; i++) {
    board[i] = calloc(8, sizeof(int));
    if (board[i] == NULL) CRASH("buy more RAM lol");
  }
  return board;
}

int **stdboard() {
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
  for (int i = 0; i < 8; i++) {
    board[1][i] = BLACK + PAWN;
  }

  for (int i = 0; i < 8; i++) {
    board[6][i] = WHITE + PAWN;
  }
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

void write_board(int **source, int **destination) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      destination[i][j] = source[i][j];
    }
  }
}

void free_board(int **board) {
  for (int i = 0; i < 8; i++) {
    free(board[i]);
  }
  free(board);
}

int **make_move(int **board, int srow, int scol, int erow, int ecol) {
  int **move_board = empty_board();
  write_board(board, move_board);
  move_board[erow][ecol] = move_board[srow][scol];
  move_board[srow][scol] = 0;
  return move_board;
}

void play_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol) {
  write_board(cur_board, prev_board);
  cur_board[erow][ecol] = cur_board[srow][scol];
  cur_board[srow][scol] = 0;
}

// TODO #1: Implement the en-passant move and the casteling move.
// These moves influence all the called functions inside the current
// function.
bool is_legal_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol) {
  if (!is_valid_move(cur_board, prev_board, srow, scol, erow, ecol)) return false;
  int **move_made;

  if (is_in_check(cur_board)) {
    move_made = make_move(cur_board, srow, scol, erow, ecol);
    bool result = !is_in_check(move_made);
    free_board(move_made);
    return result;
  }
  move_made = make_move(cur_board, srow, scol, erow, ecol);
  if (is_in_check(move_made)) {
    free_board(move_made);
    return false;
  }
  return true;
}

bool is_valid_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol) {
  switch (cur_board[srow][scol]) {
    case PAWN:
    case PAWN + BLACK: {
      return is_valid_pawn_move(cur_board, prev_board, srow, scol, erow, ecol);
    }
    case KNIGHT:
    case KNIGHT + BLACK: {
      return true;
    }
    case BISHOP:
    case BISHOP + BLACK: {
      return true;
    }
    case ROOK:
    case ROOK + BLACK: {
      return true;
    }
    case QUEEN:
    case QUEEN + BLACK: {
      return true;
    }
    case KING:
    case KING + BLACK: {
      return true;
    }
    default: {
      CRASH("Unexpected piece found during the move validation. Piece: %d", cur_board[srow][scol]);
    }
  }
}

bool is_valid_pawn_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol) {
  Moves *moves;
  INIT_MOVES(moves);
  bool is_white = is_white_piece(cur_board[srow][scol]);
  int direction = is_white ? -1 : 1;

  if ((is_white && srow == 6) || (!is_white && srow == 1)) {
    if (is_empty(cur_board[srow + direction * 2][scol])) ADD_MOVE(moves, srow + direction * 2, scol);
  }
  if (is_empty(cur_board[srow + direction][scol])) ADD_MOVE(moves, srow + direction, scol);
  if (is_in_board_limit(scol + 1) && is_white != is_white_piece(cur_board[srow + direction][scol + 1])) ADD_MOVE(moves, srow + direction, scol + 1);
  if (is_in_board_limit(scol - 1) && is_white != is_white_piece(cur_board[srow + direction][scol - 1])) ADD_MOVE(moves, srow + direction, scol - 1);

  bool result = is_in_moves(moves, erow, ecol);
  MOVES_DESTROY(moves);
  return result;
}

// TODO #2: Implement.
bool is_in_check(int **board) {
  return false;
}

bool is_in_board_limit(const int axis) {
  return axis >= 0 || axis <= 7;
}

bool can_move(const Moves *moves) {
  return moves->size != 0;
}

bool is_in_moves(const Moves *moves, int row, int col) {
  for (size_t i = 0; i < moves->size; i++) {
    if (moves->elems[i][0] == row && moves->elems[i][1] == col) return true;
  }
  return false;
}

bool is_white_piece(const int piece) {
  return piece - BLACK != abs(piece - BLACK);
}

bool is_empty(const int tile) {
  return tile == 0;
}
