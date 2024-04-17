#include "cheezee.h"
#include "backend.h"
#include "frontend.h"

void play(Program *program) {
  WIN *help;
  WIN *help_text;
  WIN *log;
  WIN *log_text;

  CREATE_WINDOW(help, ceil(program->y * 0.4), program->x - (TILE_WIDTH * 8 + 2), program->y - (program->y * 0.4), TILE_WIDTH * 8 + 2);
  CREATE_WINDOW(help_text, help->y * 0.8, help->x * 0.8, help->start_y + 2, help->start_x + 5);
  wattron(help_text->win, A_REVERSE);
  wprintw(help_text->win, "\u2190 \u2191 \u2192 \u2193");
  wattroff(help_text->win, A_REVERSE);
  wprintw(help_text->win, " move around the board\n\n");
  wattron(help_text->win, A_REVERSE);
  wprintw(help_text->win, "Enter");
  wattroff(help_text->win, A_REVERSE);
  wprintw(help_text->win, " select and submit an action");
  box(help->win, 0, 0);
  wrefresh(help->win);
  wrefresh(help_text->win);

  CREATE_WINDOW(log, program->y * 0.6, program->x - (TILE_WIDTH * 8 + 2), 0, TILE_WIDTH * 8 + 2);
  CREATE_WINDOW(log_text, log->y * 0.8, log->x * 0.8, log->start_x + 5, log->start_y + 5);
  mvwprintw(log->win, 1, 5, "Moves log");
  box(log->win, 0, 0);
  wrefresh(log->win);
  wrefresh(log_text->win);

  int **cur_board = start_standard_board();
  int **prev_board = start_standard_board();
  int row = 0;
  int col = 0;
  int input;

  draw_board(program);
  draw_pieces(program, cur_board);
  highlight_tile(program, row, col);
  keypad(program->board->win, true);
  do {
    input = wgetch(program->board->win);
    switch (input) {
      case KEY_UP: {
        if (row > 0) {
          draw_tile_row_col(program, row, col, (row + col) % 2 == 0 ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          row--;
          highlight_tile(program, row, col);
        }
        break;
      }
      case KEY_DOWN: {
        if (row < 7) {
          draw_tile_row_col(program, row, col, (row + col) % 2 == 0 ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          row++;
          highlight_tile(program, row, col);
        }
        break;
      }
      case KEY_LEFT: {
        if (col > 0) {
          draw_tile_row_col(program, row, col, (row + col) % 2 == 0 ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          col--;
          highlight_tile(program, row, col);
        }
        break;
      }
      case KEY_RIGHT: {
        if (col < 7) {
          draw_tile_row_col(program, row, col, (row + col) % 2 == 0 ? '#' : '~');
          draw_piece(program, row, col, cur_board[row][col]);
          col++;
          highlight_tile(program, row, col);
        }
        break;
      }
      case ENTER: {
        ASSERT(false, "not implemeted\n");
      }
      default: {
        break;
      }
    }
  } while (input != 'Q' && input != 'q');
  DESTROY_WINDOW(help);
  DESTROY_WINDOW(help_text);
  DESTROY_WINDOW(log);
  DESTROY_WINDOW(log_text);
  DESTROY_WINDOW(program->board);
  for (int i = 0; i < 8; i++) {
    free(cur_board[i]);
    free(prev_board[i]);
  }
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

bool is_white_piece(const int piece) {
  return piece - BLACK != abs(piece - BLACK);
}
