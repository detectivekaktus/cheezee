#include "frontend.h"

void init_board(Program *program) {
  draw_board(program);
}

void draw_board(Program *program) {
  WIN *board;
  CREATE_WINDOW(board, TILE_HEIGHT * 8 + 2, TILE_WIDTH * 8 + 2, 0, 0);
  program->board = board;
  wmove(board->win, 1, 1);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((i + j) % 2 == 0) {
        if (j == 7) draw_tile_ln(program, '#');
        else draw_tile(program, '#');
      } else {
        if (j == 7) draw_tile_ln(program, '~');
        else draw_tile(program, '~');
      }
    } 
  }
  box(board->win, 0, 0);
  wrefresh(board->win);
}

void draw_tile(Program *program, const char c) {
  if (getcury(program->board->win) != 1) wmove(program->board->win, getcury(program->board->win) - TILE_HEIGHT + 1, getcurx(program->board->win));
  char row[TILE_WIDTH + 1];
  for (int i = 0; i < TILE_WIDTH; i++) {
    row[i] = c;
  }
  row[TILE_WIDTH] = '\0';
  wprintw(program->board->win, "%s", row);
  for (int i = 0; i < TILE_HEIGHT - 1; i++) {
    mvwprintw(program->board->win, getcury(program->board->win) + 1, getcurx(program->board->win) - TILE_WIDTH, "%s", row);
  }
}

void draw_tile_ln(Program *program, const char c) {
  draw_tile(program, c);
  wmove(program->board->win, getcury(program->board->win) + TILE_HEIGHT, 1);
}
