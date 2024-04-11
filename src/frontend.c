#include "frontend.h"
#include "backend.h"
#include "cheezee.h"

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

void draw_tile(const Program *program, const char c) {
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

void draw_tile_ln(const Program *program, const char c) {
  draw_tile(program, c);
  wmove(program->board->win, getcury(program->board->win) + TILE_HEIGHT, 1);
}

void draw_pieces(const Program *program, int **board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      draw_piece(program, i, j, board[i][j]);
    }
  }
}

char *assign_piece(int piece) {
  switch (piece) {
    case PAWN: {
      return PAWN_STR;
    }
    case KNIGHT: {
      return KNIGHT_STR;
    }
    case BISHOP: {
      return BISHOP_STR;
    }
    case ROOK: {
      return ROOK_STR;
    }
    case QUEEN: {
      return QUEEN_STR;
    }
    case KING: {
      return KING_STR;
    }
    case 0: {
      return "";
    }
    default: {
      CRASH("Non-existing piece found. The piece gotten: %d", piece);
    }
  }
}

void draw_piece(const Program *program, const int row, const int col, const int piece) {
  char *piece_str;
  wmove(program->board->win, row * TILE_HEIGHT + 1, col * TILE_WIDTH + 1);
  if (is_white(piece)) {
    piece_str = assign_piece(piece);
  } else {
    piece_str = assign_piece(piece - BLACK);
  }

  int i = 0;
  while (piece_str[i] != '\0') {
    switch (piece_str[i]) {
      case ' ': {
        wmove(program->board->win, getcury(program->board->win), getcurx(program->board->win) + 1);
        i++;
        break;
      }
      case '\n': {
        wmove(program->board->win, getcury(program->board->win) + 1, getcurx(program->board->win) - TILE_WIDTH);
        i++;
        break;
      }
      default: {
        wprintw(program->board->win, "%c", piece_str[i]);
        i++;
      }
    }
  }
}

void update_board(const Program *program, int **cur_board, int **prev_board) {
  int row = 0;
  int col = 0;
  while (row != 8) {
    if (cur_board[row][col] != prev_board[row][col]) {
      draw_piece(program, row, col, cur_board[row][col]);
    }
    if (col == 7) {
      col = 0;
      row++;
    } else {
      col++;
    }
  }
}
