#ifndef CHEEZEE_FRONTEND__
#define CHEEZEE_FRONTEND__

#include "cheezee.h"

#define TILE_HEIGHT  5
#define TILE_WIDTH   15

void init_board(Program *program);
void draw_board(Program *program);
void draw_tile(Program *program, const char c);
void draw_tile_ln(Program *program, const char c);

#endif // CHEEZEE_FRONTEND__
