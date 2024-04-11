#ifndef CHEEZEE_FRONTEND__
#define CHEEZEE_FRONTEND__

#include "cheezee.h"

#define TILE_HEIGHT 5 
#define TILE_WIDTH  15

#define PAWN_STR   "      ███      \n    ███████    \n      ███      \n    ███████    \n  ███████████  "
#define KNIGHT_STR "     ██████    \n  ██████████   \n     █████     \n    ███████    \n  ███████████  "
#define BISHOP_STR "    ██ ████    \n     ██ ██     \n      ███      \n    ███████    \n  ███████████  "
#define ROOK_STR   "  ██  ███  ██  \n  ███████████  \n     █████     \n   █████████   \n  ███████████  "
#define QUEEN_STR  " ██  ██ ██  ██ \n   █████████   \n     █████     \n    ███████    \n  ███████████  "
#define KING_STR   "     █████     \n      ███      \n  ███████████  \n    ███████    \n  ███████████  "

void draw_board(Program *program);
void draw_tile(const Program *program, const char c);
void draw_tile_ln(const Program *program, const char c);
void update_board(const Program *program, int **cur_board, int **prev_board);
char *assign_piece(int piece);
void draw_pieces(const Program *program, int **board);
void draw_piece(const Program *program, const int row, const int col, const int piece);

#endif // CHEEZEE_FRONTEND__
