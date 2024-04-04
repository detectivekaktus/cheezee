#ifndef CHEEZEE_MAIN__
#define CHEEZEE_MAIN__

#include "cheezee.h"

#define ENTER 0xA
#define ESCAPE 0x1B

void finish(Program *program);
void draw_options(Program *program, char **options, int option);
int main(void);

#endif // CHEEZEE_MAIN__
