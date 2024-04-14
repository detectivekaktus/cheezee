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

#define BOARD_WHITE_COLOR   10
#define BOARD_BLACK_COLOR   11
#define PIECE_WHITE_COLOR   12
#define PIECE_BLACK_COLOR   13
#define SELECTION_COLOR     14
#define POSSIBLE_MOVE_COLOR 15
#define KING_ATTACK_COLOR   16
#define BOARD_WHITE         20
#define BOARD_BLACK         21
#define PIECE_WHITE         22
#define PIECE_BLACK         23
#define SELECTION           24
#define POSSIBLE_MOVE       25
#define KING_ATTACK         26

void init_colors();
void draw_board(Program *program);
void draw_tile(const Program *program, const char c);
void draw_tile_ln(const Program *program, const char c);
void draw_tile_row_col(const Program *program, const int row, const int col, const char c);
void highlight_tile(const Program *program, const int row, const int col);
void update_board(const Program *program, int **cur_board, int **prev_board);
char *assign_piece(int piece);
void draw_pieces(const Program *program, int **board);
void draw_piece(const Program *program, const int row, const int col, const int piece);

#endif // CHEEZEE_FRONTEND__
