#ifndef CHEEZEE_BACKEND__
#define CHEEZEE_BACKEND__

#include "cheezee.h"
#include "board.h"
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
  int **elems;
  size_t size;
  size_t capacity;
} Moves;

#define MAX_KNIGHT_MOVES 8
#define MAX_KING_MOVES   8

#define INIT_MOVES(obj)                                                       \
  do {                                                                        \
    obj = malloc(sizeof(Moves));                                              \
    (obj)->elems = calloc(1, sizeof(int *));                                  \
    if ((obj)->elems == NULL) CRASH("buy more RAM lol");                      \
    (obj)->size = 0;                                                          \
    (obj)->capacity = 1;                                                      \
  } while (0)

#define ADD_MOVE(obj, y, x)                                                   \
  do {                                                                        \
    if ((obj)->size == (obj)->capacity) {                                     \
      (obj)->capacity *= 2;                                                   \
      (obj)->elems = realloc((obj)->elems, (obj)->capacity * sizeof(int *));  \
      if ((obj)->elems == NULL) CRASH("buy more RAM lol");                    \
    }                                                                         \
    (obj)->elems[(obj)->size] = calloc(2, sizeof(int));                       \
    (obj)->elems[(obj)->size][0] = y;                                         \
    (obj)->elems[(obj)->size][1] = x;                                         \
    (obj)->size++;                                                            \
  } while (0)

#define MOVES_DESTROY(obj)                                                    \
  do {                                                                        \
    for (size_t i = 0; i < (obj)->size; i++) {                                \
      free((obj)->elems[i]);                                                  \
    }                                                                         \
    free((obj)->elems);                                                       \
    free(obj);                                                                \
  } while (0)

#define CONTINUE  1 << 6
#define STALEMATE 1 << 7
#define CHECKMATE 1 << 8

void play(Program *program);
Board *make_move(Board *board, int srow, int scol, int erow, int ecol);
void play_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_legal_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_casteling_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_legal_casteling_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_pawn_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_knight_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_bishop_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_rook_move(Board *board, int srow, int scol, int erow, int ecol);
bool is_valid_king_move(Board *board, int srow, int scol, int erow, int ecol);
void traverse_axis(Moves *moves, Board *board, int row, int col, const int deltarow, const int deltacol, const bool is_white);
Moves *get_moves(Board *board, const int piece, int row, int col);
Moves *get_pawn_moves(Board *board, int row, int col);
Moves *get_knight_moves(Board *board, int row, int col);
Moves *get_bishop_moves(Board *board, int row, int col);
Moves *get_rook_moves(Board *board, int row, int col);
Moves *get_queen_moves(Board *board, int row, int col);
Moves *get_king_moves(Board *board, int row, int col);
bool is_in_check(Board *board);
bool has_legal_moves(Board *board);
int update_game_state(Board *board);
bool is_in_board_limit(const int axis);
bool can_move(const Moves *moves);
bool is_in_moves(const Moves *moves, int row, int col);
bool is_white_piece(const int piece);
bool is_empty(const int tile);

#endif // CHEEZEE_BACKEND__
