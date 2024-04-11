#include "cheezee.h"
#include "backend.h"
#include "frontend.h"

void play(Program *program) {
  int **cur_board = start_standard_board();
  int **prev_board = start_standard_board();

  draw_board(program);
  draw_pieces(program, cur_board);
  int input;
  do {
    input = wgetch(program->board->win);
  } while (input != 'Q' && input != 'q');
  free(cur_board);
  free(prev_board);
}

int **start_standard_board() {
  int **board = calloc(8, sizeof(int *));
  if (board == NULL) CRASH("buy more RAM lol");
  for (int i = 0; i < 8; i++) {
    board[i] = calloc(8, sizeof(int));
    if (board[i] == NULL) CRASH("buy more RAM lol");
  }
  board[0][0] = BLACK + ROOK;
  board[0][1] = BLACK + KNIGHT;
  board[0][2] = BLACK + BISHOP;
  board[0][3] = BLACK + QUEEN;
  board[0][4] = BLACK + KING;
  board[0][5] = BLACK + BISHOP;
  board[0][6] = BLACK + KNIGHT;
  board[0][7] = BLACK + ROOK;
  for (int i = 0; i < 8; i++) board[1][i] = BLACK + PAWN;

  for (int i = 0; i < 8; i++) board[6][i] = WHITE + PAWN;
  board[7][0] = WHITE + ROOK;
  board[7][1] = WHITE + KNIGHT;
  board[7][2] = WHITE + BISHOP;
  board[7][3] = WHITE + QUEEN;
  board[7][4] = WHITE + KING;
  board[7][5] = WHITE + BISHOP;
  board[7][6] = WHITE + KNIGHT;
  board[7][7] = WHITE + ROOK;
  return board;
}

bool is_white(const int piece) {
  return piece - BLACK != abs(piece - BLACK);
}
