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

typedef struct {
  int **moves;
  size_t size;
  size_t capacity;
} Moves;

#define MOVES_INIT(arr) \
  do { \
    arr = malloc(sizeof(Moves)); \
    if (arr == NULL) CRASH("buy more RAM lol"); \
    (arr)->moves = calloc(1, sizeof(int *)); \
    if ((arr)->moves == NULL) CRASH("buy more RAM lol"); \
    (arr)->size = 0; \
    (arr)->capacity = 1; \
  } while(0)

#define MOVES_ADD(arr, y, x) \
  do { \
    if ((arr)->size == (arr)->capacity) { \
      (arr)->capacity *= 2; \
      (arr)->moves = realloc((arr)->moves, (arr)->capacity * sizeof(int *)); \
      if ((arr)->moves == NULL) CRASH("buy more RAM lol"); \
    } \
    int *move = calloc(2, sizeof(int)); \
    if (move == NULL) CRASH("buy more RAM lol"); \
    move[0] = y; \
    move[1] = x; \
    (arr)->moves[(arr)->size] = move; \
    (arr)->size++; \
  } while(0)

#define MOVES_DESTROY(arr) \
  do { \
    for (size_t i = 0; i < (arr)->capacity; i++) { \
      free((arr)->moves[i]); \
    } \
    free((arr)->moves); \
    free(arr); \
  } while(0)

void play(Program *program);
int **start_standard_board();
void write_board(int **source, int **destination);
Moves *get_moves(int **board, const int row, const int col);
Moves *get_pawn_moves(int **board, int row, int col);
Moves *get_knight_moves(int **board, int row, int col);
Moves *get_bishop_moves(int **board, int row, int col);
Moves *get_rook_moves(int **board, int row, int col);
Moves *get_queen_moves(int **board, int row, int col);
Moves *get_king_moves(int **board, int row, int col);
bool is_valid_move(const int piece, const int start_row, const int start_col, const int end_row, const int end_col);
bool is_valid_pawn_move(const int start_row, const int start_col, const int end_row, const int end_col);
bool is_valid_knight_move(const int start_row, const int start_col, const int end_row, const int end_col);
bool is_valid_bishop_move(const int start_row, const int start_col, const int end_row, const int end_col);
bool is_valid_rook_move(const int start_row, const int start_col, const int end_row, const int end_col);
bool is_valid_queen_move(const int start_row, const int start_col, const int end_row, const int end_col);
bool is_valid_king_move(const int start_row, const int start_col, const int end_row, const int end_col);
void traverse_diagonal(Moves *moves, int **board, int row, int col, int inc_y, int inc_x, const bool is_white);
void traverse_vertical(Moves *moves, int **board, int row, int col, int inc, const bool is_white);
void traverse_horizontal(Moves *moves, int **board, int row, int col, int inc, const bool is_white);
bool is_in_board_limit(const int axis);
bool can_move(const Moves *moves);
bool is_white_piece(const int piece);
bool is_empty(const int tile);

#endif // CHEEZEE_BACKEND__
