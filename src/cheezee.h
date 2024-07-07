#ifndef CHEEZEE_H__
#define CHEEZEE_H__

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ENTER  0xA
#define ESCAPE 0x1B

#define CRASH(msg, ...)                                                           \
  do {                                                                            \
    endwin();                                                                     \
    fprintf(stderr, msg, ##__VA_ARGS__);                                          \
    exit(1);                                                                      \
  } while(0)

#define LOG(msg, ...)                                                             \
  do {                                                                            \
    FILE *logfile = fopen(".log", "a");                                           \
    fprintf(logfile, msg, ##__VA_ARGS__);                                         \
    fclose(logfile);                                                              \
  } while(0)

#define ASSERT(cond, msg, ...)                                                    \
  do {                                                                            \
    if (!cond) {                                                                  \
      endwin();                                                                   \
      fprintf(stderr, "Assertion failed at: %s, line %d.\n", __FILE__, __LINE__); \
      fprintf(stderr, msg, ##__VA_ARGS__);                                        \
      exit(1);                                                                    \
    }                                                                             \
  } while(0)

typedef struct {
  WINDOW *win;
  int x;
  int y;
  int start_x;
  int start_y;
} WIN;

#define CREATE_CENTERED_WINDOW(parent, window, size_y, size_x)                              \
  do {                                                                                      \
    window = malloc(sizeof(WIN));                                                           \
    if (window == NULL) CRASH("buy more RAM lol");                                          \
    (window)->y = size_y;                                                                   \
    (window)->x = size_x;                                                                   \
    (window)->start_y = ((parent)->y - (window)->y) / 2;                                    \
    (window)->start_x = ((parent)->x - (window)->x) / 2;                                    \
    (window)->win = newwin((window)->y, (window)->x, (window)->start_y, (window)->start_x); \
  } while(0)

#define CREATE_WINDOW(window, size_y, size_x, starty, startx)                               \
  do {                                                                                      \
    window = malloc(sizeof(WIN));                                                           \
    if (window == NULL) CRASH("buy more RAM lol");                                          \
    (window)->y = size_y;                                                                   \
    (window)->x = size_x;                                                                   \
    (window)->start_y = starty;                                                             \
    (window)->start_x = startx;                                                             \
    (window)->win = newwin((window)->y, (window)->x, starty, startx);                       \
  } while(0)

#define DESTROY_WINDOW(window)                                                              \
  do {                                                                                      \
    delwin((window)->win);                                                                  \
    free(window);                                                                           \
    window = NULL;                                                                          \
  } while(0)

typedef struct {
  int x;
  int y;

  WIN *main_menu;
  WIN *board;
} Program;

typedef struct {
  char *content;
  size_t size;
  size_t capacity;
} String;

#define CREATE_STRING(str)                                                        \
  do {                                                                            \
    str = malloc(sizeof(String));                                                 \
    (str)->size = 1;                                                              \
    (str)->capacity = 1;                                                          \
    (str)->content = calloc((str)->capacity, sizeof(char));                       \
    (str)->content[0] = '\0';                                                     \
  } while(0)

#define STRING_APPEND(str, val)                                                   \
  do {                                                                            \
    if ((str)->size + 1 >= (str)->capacity) {                                     \
      (str)->capacity *= 2;                                                       \
      (str)->content = realloc((str)->content, (str)->capacity * sizeof(char));   \
    }                                                                             \
    (str)->content[(str)->size - 1] = val;                                        \
    (str)->content[(str)->size] = '\0';                                           \
    (str)->size++;                                                                \
  } while(0)

/* 
* For a few ones who are going to analyze this code,
* yes this macro can segfault, but it won't happen,
* cause it's handled properly in the main.c file.
*/
#define STRING_POP(str)                                                           \
  do {                                                                            \
    (str)->size--;                                                                \
    (str)->content[(str)->size] = 0;                                              \
    (str)->content[(str)->size - 1] = '\0';                                       \
  } while(0)

#define DESTROY_STRING(str)                                                       \
  do {                                                                            \
    free((str)->content);                                                         \
    free(str);                                                                    \
    str = NULL;                                                                   \
  } while(0)


#endif // CHEEZEE_H__
