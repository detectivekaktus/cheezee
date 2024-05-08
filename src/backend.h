#ifndef CHEEZEE_BACKEND__
#define CHEEZEE_BACKEND__

#include "cheezee.h"
#include <math.h>

#define WHITE  0
#define BLACK  18

#define PAWN   1
#define KNIGHT 3
#define BISHOP 4
#define ROOK   5
#define QUEEN  9
#define KING   10

void play(Program *program);
int **empty_board();
int **stdboard();
void write_board(int **source, int **destination);
void free_board(int **board);
int **make_move(int **board, int start_row, int start_col, int end_row, int end_col);
void play_move(int **cur_board, int **prev_board, int start_row, int start_col, int end_row, int end_col);
bool is_legal_move(int **board, int start_row, int start_col, int end_row, int end_col);
bool is_in_check(int **board);
bool is_in_board_limit(const int axis);
bool is_white_piece(const int piece);
bool is_empty(const int tile);

#endif // CHEEZEE_BACKEND__
