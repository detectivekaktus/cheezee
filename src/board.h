#ifndef CHEEZEE_BOARD_H__
#define CHEEZEE_BOARD_H__

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

typedef struct {
  char *content;
  size_t size;
  size_t capacity;
} FenString;

#define FEN_START(str)                                       \
  do {                                                       \
    str = malloc(sizeof(FenString));                         \
    (str)->size = 1;                                         \
    (str)->capacity = 64;                                    \
    (str)->content = calloc((str)->capacity, sizeof(char));  \
    (str)->content[0] = '\0';                                \
  } while(0)

/* 
* For a few ones who are going to analyze this code,
* yes this macro can segfault, but it won't happen,
* cause it's handled properly in the main.c file.
*/
#define FEN_APPEND(str, val)                                 \
  do {                                                       \
    (str)->content[(str)->size - 1] = val;                   \
    (str)->content[(str)->size] = '\0';                      \
    (str)->size++;                                           \
  } while(0)

/*
* The same applies for this macro, but it's handled
* properly in the same main.c file.
*/
#define FEN_POP(str)                                         \
  do {                                                       \
    (str)->size--;                                           \
    (str)->content[(str)->size] = 0;                         \
    (str)->content[(str)->size - 1] = '\0';                  \
  } while(0)

#define DESTROY_FEN(str)                                     \
  do {                                                       \
    free((str)->content);                                    \
    free(str);                                               \
    str = NULL;                                              \
  } while(0)

Board *start_board();
Board *board_from_fen(FenString *str);
void copy_board(const Board *source, Board *destination);
void delete_board(Board *board);
int **empty_matrix();
int **stdmatrix();
void write_matrix(int **source, int **destination);
void free_matrix(int **board);

#endif // CHEEZEE_BOARD_H__
