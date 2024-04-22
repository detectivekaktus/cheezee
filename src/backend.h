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
int **start_standard_board();
Moves *get_moves(int **board, const int row, const int col);
Moves *get_pawn_moves(int **board, int row, int col);
Moves *get_bishop_moves(int **board, int row, int col);
Moves *get_rook_moves(int **board, int row, int col);
Moves *get_queen_moves(int **board, int row, int col);
Moves *get_king_moves(int **board, int row, int col);
void traverse_diagonal(Moves *moves, int **board, int row, int col, int inc_y, int inc_x, const bool is_white);
void traverse_vertical(Moves *moves, int **board, int row, int col, int inc, const bool is_white);
void traverse_horizontal(Moves *moves, int **board, int row, int col, int inc, const bool is_white);
bool is_in_board_limit(const int axis);
bool can_move(const Moves *moves);
bool is_white_piece(const int piece);
bool is_empty(const int tile);

#endif // CHEEZEE_BACKEND__
