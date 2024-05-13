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
  int **elems;
  size_t size;
  size_t capacity;
} Moves;

#define MAX_KNIGHT_MOVES 8

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

void play(Program *program);
int **empty_board();
int **stdboard();
void write_board(int **source, int **destination);
void free_board(int **board);
int **make_move(int **board, int srow, int scol, int erow, int ecol);
void play_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol);
bool is_legal_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol);
bool is_valid_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol);
bool is_valid_pawn_move(int **cur_board, int **prev_board, int srow, int scol, int erow, int ecol);
bool is_valid_knight_move(int **board, int srow, int scol, int erow, int ecol);
bool is_valid_bishop_move(int **board, int srow, int scol, int erow, int ecol);
bool is_valid_rook_move(int **board, int srow, int scol, int erow, int ecol);
void traverse_axis(Moves *moves, int **board, int row, int col, const int deltarow, const int deltacol, const bool is_white);
bool is_in_check(int **board);
bool is_in_board_limit(const int axis);
bool can_move(const Moves *moves);
bool is_in_moves(const Moves *moves, int row, int col);
bool is_white_piece(const int piece);
bool is_empty(const int tile);

#endif // CHEEZEE_BACKEND__
