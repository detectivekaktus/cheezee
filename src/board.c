#include "backend.h"
#include "cheezee.h"
#include <string.h>
#include "board.h"

Board *start_board() {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) CRASH("buy more RAM lol");
  board->current = stdmatrix();
  board->previous = empty_matrix();
  board->is_white_turn = true;
  board->has_white_king_moved = false;
  board->has_white_king_casteled = false;
  board->white_king_row = 7;
  board->white_king_col = 4;
  board->has_white_left_rook_moved = false;
  board->has_white_right_rook_moved = false;
  board->has_black_king_moved = false;
  board->has_white_king_casteled = false;
  board->black_king_row = 0;
  board->black_king_col = 4;
  board->has_black_left_rook_moved = false;
  board->has_black_right_rook_moved = false;
  board->game_state = CONTINUE;
  return board;
}

Board *board_from_fen(char *str) {
  Board *board = malloc(sizeof(Board));
  board->current = empty_matrix();
  board->previous = empty_matrix();
  int splits = 0;
  char *piece = strtok(str, " ");
  while (piece != NULL) {
    splits++;
    if (splits > 3) {
      CRASH("FEN syntax error. Expected FEN string of type 'BOARD MOVE CASTELING'.\n");
    } else if (splits == 1) {
      parse_fen(piece, board);
    } else if (splits == 2) {
      board->is_white_turn = piece[0] == 'w';
    } else if (splits == 3) {
      parse_casteling(piece, board);
    }
    piece = strtok(NULL, " ");
  }
  board->game_state = CONTINUE;
  return board;
}

void parse_fen(const char *str, Board *board) {
  int i = 0;
  int row = 0;
  int col = 0;
  while (str[i] != '\0') {
    switch (str[i]) {
      case 'r': {
        board->current[row][col] = ROOK + BLACK;
        if (col < 7) col++;
        break;
      }
      case 'R': {
        board->current[row][col] = ROOK;
        if (col < 7) col++;
        break;
      }
      case 'n': {
        board->current[row][col] = KNIGHT + BLACK;
        if (col < 7) col++;
        break;
      }
      case 'N': {
        board->current[row][col] = KNIGHT;
        if (col < 7) col++;
        break;
      }
      case 'b': {
        board->current[row][col] = BISHOP + BLACK;
        if (col < 7) col++;
        break;
      }
      case 'B': {
        board->current[row][col] = BISHOP;
        if (col < 7) col++;
        break;
      }
      case 'q': {
        board->current[row][col] = QUEEN + BLACK;
        if (col < 7) col++;
        break;
      }
      case 'Q': {
        board->current[row][col] = QUEEN;
        if (col < 7) col++;
        break;
      }
      case 'k': {
        board->black_king_col = col;
        board->black_king_row = row;
        board->current[row][col] = KING + BLACK;
        if (col < 7) col++;
        break;
      }
      case 'K': {
        board->white_king_col = col;
        board->white_king_row = row;
        board->current[row][col] = KING;
        if (col < 7) col++;
        break;
      }
      case 'p': {
        board->current[row][col] = PAWN + BLACK;
        if (col < 7) col++;
        break;
      }
      case 'P': {
        board->current[row][col] = PAWN;
        if (col < 7) col++;
        break;
      }
      case '/': {
        if (row == 7) CRASH("FEN syntax error. The board cannot be larger than 8x8.\n");
        row++;
        col = 0;
        break;
      }
      default: {
        if (str[i] > 48 && str[i] < 57) {
          col += str[i] - 48;
        } else {
          CRASH("FEN syntax error. Unknown character '%c'\n", str[i]);
        }
      }
    }
    i++;
  }
}

void parse_casteling(const char *str, Board *board) {
  if (strchr(str, 'K') == NULL || strchr(str, 'Q') == NULL) {
    board->has_white_king_casteled = true;
    board->has_white_king_moved = true;
    board->has_white_right_rook_moved = false;
    board->has_white_left_rook_moved = false;
  } else {
    board->has_white_king_casteled = false;
    board->has_white_king_moved = false;
    board->has_white_right_rook_moved = false;
    board->has_white_left_rook_moved = false;
  }
  if (strchr(str, 'k') == NULL || strchr(str, 'q') == NULL) {
    board->has_black_king_casteled = true;
    board->has_black_king_moved = true;
    board->has_black_right_rook_moved = false;
    board->has_black_left_rook_moved = false;
  } else {
    board->has_black_king_casteled = false;
    board->has_black_king_moved = false;
    board->has_black_right_rook_moved = false;
    board->has_black_left_rook_moved = false;
  }
}

void copy_board(const Board *source, Board *destination) {
  destination->current = empty_matrix();
  write_matrix(source->current, destination->current);
  destination->previous = empty_matrix();
  write_matrix(source->previous, destination->previous);
  destination->is_white_turn = source->is_white_turn;
  destination->has_white_king_moved = source->has_white_king_moved;
  destination->has_white_king_casteled = source->has_white_king_casteled;
  destination->white_king_row = source->white_king_row;
  destination->white_king_col = source->white_king_col;
  destination->has_white_left_rook_moved = source->has_white_left_rook_moved;
  destination->has_white_right_rook_moved = source->has_white_right_rook_moved;
  destination->has_black_king_moved = source->has_black_king_moved;
  destination->has_black_king_casteled = source->has_black_king_casteled;
  destination->black_king_row = source->black_king_row;
  destination->black_king_col = source->black_king_col;
  destination->has_black_left_rook_moved = source->has_black_left_rook_moved;
  destination->has_black_right_rook_moved = source->has_black_right_rook_moved;
  destination->game_state = source->game_state;
}

void delete_board(Board *board) {
  free_matrix(board->current);
  free_matrix(board->previous);
  free(board);
}

int **empty_matrix() {
  int **board = calloc(8, sizeof(int *));
  if (board == NULL) CRASH("buy more RAM lol");
  for (int i = 0; i < 8; i++) {
    board[i] = calloc(8, sizeof(int));
    if (board[i] == NULL) CRASH("buy more RAM lol");
  }
  return board;
}

int **stdmatrix() {
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
  for (int i = 0; i < 8; i++) {
    board[1][i] = BLACK + PAWN;
  }

  for (int i = 0; i < 8; i++) {
    board[6][i] = WHITE + PAWN;
  }
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

void write_matrix(int **source, int **destination) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      destination[i][j] = source[i][j];
    }
  }
}

void free_matrix(int **board) {
  for (int i = 0; i < 8; i++) {
    free(board[i]);
  }
  free(board);
}

