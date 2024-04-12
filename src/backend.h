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

void play(Program *program);
int **start_standard_board();
bool is_white(const int piece);

#endif // CHEEZEE_BACKEND__
