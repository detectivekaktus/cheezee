#ifndef CHEEZEE_MAIN__
#define CHEEZEE_MAIN__

#include "cheezee.h"

#define ENTER     0xA
#define ESCAPE    0x1B

#define NEW_GAME  0x0
#define FEN_POS   0x1
#define CREDITS   0x2
#define EXIT      0x3

void finish(Program *program);
void draw_options(Program *program, char **options, int option);
int main(void);

#endif // CHEEZEE_MAIN__
