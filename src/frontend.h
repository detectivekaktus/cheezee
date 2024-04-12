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

#define BOARD_WHITE_COLOR   1
#define BOARD_BLACK_COLOR   2
#define PIECE_WHITE_COLOR   3
#define PIECE_BLACK_COLOR   4
#define SELECTION_COLOR     5
#define POSSIBLE_MOVE_COLOR 6
#define KING_ATTACK_COLOR   7
#define BOARD_WHITE         11
#define BOARD_BLACK         12
#define PIECE_WHITE         13
#define PIECE_BLACK         14
#define SELECTION           15
#define POSSIBLE_MOVE       16
#define KING_ATTACK         17

void init_colors();
void draw_board(Program *program);
void draw_tile(const Program *program, const char c);
void draw_tile_ln(const Program *program, const char c);
void update_board(const Program *program, int **cur_board, int **prev_board);
char *assign_piece(int piece);
void draw_pieces(const Program *program, int **board);
void draw_piece(const Program *program, const int row, const int col, const int piece);

#endif // CHEEZEE_FRONTEND__
