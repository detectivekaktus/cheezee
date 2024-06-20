#include "backend.h"
#include "board.h"

Board *start_board() {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) CRASH("buy more RAM lol");
  board->current = stdmatrix();
  board->previous = empty_matrix();
  board->is_white_turn = true;
  board->has_white_king_moved = false;
  board->has_white_king_casteled = false;
  board->white_king_row = 7;
  board->white_king_col = 4;
  board->has_white_left_rook_moved = false;
  board->has_white_right_rook_moved = false;
  board->has_black_king_moved = false;
  board->has_white_king_casteled = false;
  board->black_king_row = 0;
  board->black_king_col = 4;
  board->has_black_left_rook_moved = false;
  board->has_black_right_rook_moved = false;
  board->game_state = CONTINUE;
  return board;
}

void copy_board(const Board *source, Board *destination) {
  destination->current = empty_matrix();
  write_matrix(source->current, destination->current);
  destination->previous = empty_matrix();
  write_matrix(source->previous, destination->previous);
  destination->is_white_turn = source->is_white_turn;
  destination->has_white_king_moved = source->has_white_king_moved;
  destination->has_white_king_casteled = source->has_white_king_casteled;
  destination->white_king_row = source->white_king_row;
  destination->white_king_col = source->white_king_col;
  destination->has_white_left_rook_moved = source->has_white_left_rook_moved;
  destination->has_white_right_rook_moved = source->has_white_right_rook_moved;
  destination->has_black_king_moved = source->has_black_king_moved;
  destination->has_black_king_casteled = source->has_black_king_casteled;
  destination->black_king_row = source->black_king_row;
  destination->black_king_col = source->black_king_col;
  destination->has_black_left_rook_moved = source->has_black_left_rook_moved;
  destination->has_black_right_rook_moved = source->has_black_right_rook_moved;
  destination->game_state = source->game_state;
}

void delete_board(Board *board) {
  free_matrix(board->current);
  free_matrix(board->previous);
  free(board);
}

int **empty_matrix() {
  int **board = calloc(8, sizeof(int *));
  if (board == NULL) CRASH("buy more RAM lol");
  for (int i = 0; i < 8; i++) {
    board[i] = calloc(8, sizeof(int));
    if (board[i] == NULL) CRASH("buy more RAM lol");
  }
  return board;
}

int **stdmatrix() {
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

void write_matrix(int **source, int **destination) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      destination[i][j] = source[i][j];
    }
  }
}

void free_matrix(int **board) {
  for (int i = 0; i < 8; i++) {
    free(board[i]);
  }
  free(board);
}

