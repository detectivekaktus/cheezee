#ifndef CHEEZEE_MAIN__
#define CHEEZEE_MAIN__

#include "cheezee.h"
#include <locale.h>

#define NEW_GAME 0
#define FEN_POS  1
#define CREDITS  2
#define EXIT     3

void finish(Program *program);
void draw_options(const Program *program, char **options, int option);
int main(int argc, char **argv);

#endif // CHEEZEE_MAIN__
