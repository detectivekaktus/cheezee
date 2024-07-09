#ifndef CHEEZEE_BOARD_H__
#define CHEEZEE_BOARD_H__

#include "cheezee.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  int **current;
  int **previous;

  bool is_white_turn;

  bool has_white_king_moved;
  bool has_white_king_casteled;
  int white_king_row;
  int white_king_col;
  bool has_white_left_rook_moved;
  bool has_white_right_rook_moved;

  bool has_black_king_moved;
  bool has_black_king_casteled;
  int black_king_row;
  int black_king_col;
  bool has_black_left_rook_moved;
  bool has_black_right_rook_moved;

  int game_state;
} Board;

Board *start_board();
Board *board_from_fen(char *str);
void parse_fen(const char *str, Board *board);
void parse_casteling(const char *str, Board *board);
void copy_board(const Board *source, Board *destination);
void delete_board(Board *board);
int **empty_matrix();
int **stdmatrix();
void write_matrix(int **source, int **destination);
void free_matrix(int **board);

#endif // CHEEZEE_BOARD_H__
