#ifndef CHEEZEE_H__
#define CHEEZEE_H__

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ENTER  0xA
#define ESCAPE 0x1B

#define CRASH(msg, ...) \
  do { \
    fprintf(stderr, msg, ##__VA_ARGS__); \
    endwin(); \
    exit(1); \
  } while(0)

#define ASSERT(cond, msg, ...) \
  do { \
    if (!cond) { \
      endwin(); \
      fprintf(stderr, "Assertion failed at: %s, line %d.\n", __FILE__, __LINE__); \
      fprintf(stderr, msg, ##__VA_ARGS__); \
      exit(1); \
    } \
  } while(0)

typedef struct {
  WINDOW *win;
  int x;
  int y;
  int start_x;
  int start_y;
} WIN;

#define CREATE_CENTERED_WINDOW(parent, window, size_y, size_x) \
  do { \
    window = malloc(sizeof(WIN)); \
    if (window == NULL) CRASH("buy more RAM lol"); \
    (window)->y = size_y; \
    (window)->x = size_x; \
    (window)->start_y = ((parent)->y - (window)->y) / 2; \
    (window)->start_x = ((parent)->x - (window)->x) / 2; \
    (window)->win = newwin((window)->y, (window)->x, (window)->start_y, (window)->start_x); \
  } while(0)

#define CREATE_WINDOW(window, size_y, size_x, starty, startx) \
  do { \
    window = malloc(sizeof(WIN)); \
    if (window == NULL) CRASH("buy more RAM lol"); \
    (window)->y = size_y; \
    (window)->x = size_x; \
    (window)->start_y = starty; \
    (window)->start_x = startx; \
    (window)->win = newwin((window)->y, (window)->x, starty, startx); \
  } while(0)

#define DESTROY_WINDOW(window) \
  do { \
    delwin((window)->win); \
    free(window); \
  } while(0)

typedef struct {
  int **moves;
  size_t size;
  size_t capacity;
} Moves;

#define MOVES_INIT(arr) \
  do { \
    arr = malloc(sizeof(Moves)); \
    if (arr == NULL) CRASH("buy more RAM lol"); \
    (arr)->moves = calloc(1, sizeof(int *)); \
    if ((arr)->moves == NULL) CRASH("buy more RAM lol"); \
    (arr)->size = 0; \
    (arr)->capacity = 1; \
  } while(0)

#define MOVES_ADD(arr, x, y) \
  do { \
    if ((arr)->size == (arr)->capacity) { \
      (arr)->capacity *= 2; \
      (arr)->moves = realloc((arr)->moves, (arr)->capacity * sizeof(int *)); \
      if ((arr)->moves == NULL) CRASH("buy more RAM lol"); \
    } \
    int *move = calloc(2, sizeof(int)); \
    if (move == NULL) CRASH("buy more RAM lol"); \
    move[0] = x; \
    move[1] = y; \
    (arr)->moves[(arr)->size] = move; \
    (arr)->size++; \
  } while(0)

#define MOVES_DESTROY(arr) \
  do { \
    for (int i = 0; i < (arr)->capacity; i++) { \
      free((arr)->moves[i]); \
    } \
    free((arr)->moves); \
    free(arr); \
  } while(0)

typedef struct {
  int x;
  int y;

  WIN *main_menu;
  WIN *board;
} Program;

#endif // CHEEZEE_H__
