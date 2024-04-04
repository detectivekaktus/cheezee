#ifndef CHEEZEE_H__
#define CHEEZEE_H__

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define CRASH(msg, ...) \
  do { \
    fprintf(stderr, msg, ##__VA_ARGS__); \
    endwin(); \
    exit(1); \
  } while(0)

typedef struct {
  int index;
  int r;
  int g;
  int b;
} Color;

typedef struct {
  WINDOW *win;
  int x;
  int y;
} WIN;

typedef struct {
  int max_x;
  int max_y;

  WIN *main_menu;
} Program;

#endif // CHEEZEE_H__
