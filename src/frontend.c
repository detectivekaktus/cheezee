#include "frontend.h"
#include "backend.h"
#include "cheezee.h"

void init_colors() {
  start_color();
  init_color(BOARD_WHITE_COLOR, 578, 578, 578);
  init_color(BOARD_BLACK_COLOR, 636, 394, 253);
  init_color(PIECE_WHITE_COLOR, 1000, 1000, 1000);
  init_color(PIECE_BLACK_COLOR, 58, 50, 46);
  init_color(SELECTION_COLOR, 58, 539, 378);
  init_color(POSSIBLE_MOVE_COLOR, 58, 457, 539);
  init_color(KING_ATTACK_COLOR, 1000, 0, 234);
  
  init_pair(BOARD_WHITE, BOARD_WHITE_COLOR, COLOR_BLACK);
  init_pair(BOARD_BLACK, BOARD_BLACK_COLOR, COLOR_BLACK);
  init_pair(PIECE_WHITE, PIECE_WHITE_COLOR, COLOR_BLACK);
  init_pair(PIECE_BLACK, PIECE_BLACK_COLOR, COLOR_BLACK);
  init_pair(SELECTION, SELECTION_COLOR, COLOR_BLACK);
  init_pair(POSSIBLE_MOVE, POSSIBLE_MOVE_COLOR, COLOR_BLACK);
  init_pair(KING_ATTACK, KING_ATTACK_COLOR, COLOR_BLACK);

  use_default_colors();
}

void draw_board(Program *program) {
  WIN *board;
  CREATE_WINDOW(board, TILE_HEIGHT * 8 + 2, TILE_WIDTH * 8 + 2, 0, 0);
  program->board = board;
  wmove(board->win, 1, 1);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (is_white_tile(i, j)) {
        wattron(board->win, COLOR_PAIR(BOARD_WHITE));
        if (j == 7) draw_tile_ln(program, '#');
        else draw_tile(program, '#');
        wattroff(board->win, COLOR_PAIR(BOARD_WHITE));
      } else {
        wattron(board->win, COLOR_PAIR(BOARD_BLACK));
        if (j == 7) draw_tile_ln(program, '~');
        else draw_tile(program, '~');
        wattroff(board->win, COLOR_PAIR(BOARD_BLACK));
      }
    } 
  }
  box(board->win, 0, 0);
  wrefresh(board->win);
}

void draw_tile(const Program *program, const char c) {
  char row[TILE_WIDTH + 1];
  for (int i = 0; i < TILE_WIDTH; i++) {
    row[i] = c;
  }
  row[TILE_WIDTH] = '\0';
  wprintw(program->board->win, "%s", row);
  for (int i = 0; i < TILE_HEIGHT - 1; i++) {
    mvwprintw(program->board->win, getcury(program->board->win) + 1, getcurx(program->board->win) - TILE_WIDTH, "%s", row);
  }
  wmove(program->board->win, getcury(program->board->win) - TILE_HEIGHT + 1, getcurx(program->board->win));
}

void draw_tile_ln(const Program *program, const char c) {
  draw_tile(program, c);
  wmove(program->board->win, getcury(program->board->win) + TILE_HEIGHT, 1);
}

void draw_tile_row_col(const Program *program, const int row, const int col, const char c) {
  wmove(program->board->win, row * TILE_HEIGHT + 1, col * TILE_WIDTH + 1);
  is_white_tile(row, col) ? wattron(program->board->win, COLOR_PAIR(BOARD_WHITE)) : wattron(program->board->win, COLOR_PAIR(BOARD_BLACK));
  draw_tile(program, c);
  is_white_tile(row, col) ? wattroff(program->board->win, COLOR_PAIR(BOARD_WHITE)) : wattroff(program->board->win, COLOR_PAIR(BOARD_BLACK));
}

void highlight_tile(const Program *program, const int row, const int col) {
  wmove(program->board->win, row * TILE_HEIGHT + 1, col * TILE_WIDTH + 1);
  for (int i = 0; i < TILE_HEIGHT; i++) {
    for (int j = 0; j < TILE_WIDTH; j++) {
      // Due to the Mingw Windows ncurses library incompatability
      // with unicode characters, we have to make a longer check for
      // tile characters and not piece characters.
      if (((winch(program->board->win) & A_CHARTEXT) == '#') || ((winch(program->board->win) & A_CHARTEXT) == '~')) {
        wattron(program->board->win, COLOR_PAIR(SELECTION));
        if (is_white_tile(row, col)) {
          wprintw(program->board->win, "#");
        } else {
          wprintw(program->board->win, "~");
        }
        wattroff(program->board->win, COLOR_PAIR(SELECTION));
      } else {
        wmove(program->board->win, getcury(program->board->win), getcurx(program->board->win) + 1);
      }
    }
    wmove(program->board->win, getcury(program->board->win) + 1, getcurx(program->board->win) - TILE_WIDTH);
  }
}

void draw_pieces(const Program *program, int **board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      draw_piece(program, i, j, board[i][j]);
    }
  }
  wrefresh(program->board->win);
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
  if (is_white_piece(piece)) {
    piece_str = assign_piece(piece);
  } else {
    piece_str = assign_piece(piece - BLACK);
  }
  
  if (strcmp(piece_str, "") == 0) {
    is_white_tile(row, col) ? wattron(program->board->win, COLOR_PAIR(BOARD_WHITE)) : wattron(program->board->win, COLOR_PAIR(BOARD_BLACK));
    draw_tile(program, is_white_tile(row, col) ? '#' : '~');
    is_white_tile(row, col) ? wattroff(program->board->win, COLOR_PAIR(BOARD_WHITE)) : wattroff(program->board->win, COLOR_PAIR(BOARD_BLACK));
  } else {
    is_white_piece(piece) ? wattron(program->board->win, COLOR_PAIR(PIECE_WHITE)) : wattron(program->board->win, COLOR_PAIR(PIECE_BLACK));
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
    is_white_piece(piece) ? wattroff(program->board->win, COLOR_PAIR(PIECE_WHITE)) : wattroff(program->board->win, COLOR_PAIR(PIECE_BLACK));
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
  wrefresh(program->board->win);
}

bool is_white_tile(const int row, const int col) {
  return (row + col) % 2 == 0;
}
