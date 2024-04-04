#include "cheezee.h"
#include "main.h"

void finish(Program *program) {
  if (program->main_menu) {
    delwin(program->main_menu->win);
    free(program->main_menu);
  }
  endwin();

  free(program);
  exit(0);
}

void draw_options(Program *program, char **options, int option) {
  for (int i = 0; i < 4; i++) {
    if (option == i) {
      wattron(program->main_menu->win, A_REVERSE);
      mvwprintw(program->main_menu->win, getcury(program->main_menu->win) + (program->main_menu->y * 20) / 100, (program->main_menu->x - strlen(options[i])) / 2, options[i]);
      wattroff(program->main_menu->win, A_REVERSE);
    } else {
      mvwprintw(program->main_menu->win, getcury(program->main_menu->win) + (program->main_menu->y * 20) / 100, (program->main_menu->x - strlen(options[i])) / 2, options[i]);
    }
  }
  wmove(program->main_menu->win, 0, 0);
  wrefresh(program->main_menu->win);
}

int main(void) {
  Program *program = malloc(sizeof(Program));

  initscr();
  cbreak();
  noecho();
  getmaxyx(stdscr, program->max_y, program->max_x);
  if (!has_colors()) CRASH("Your terminal does not support colors.");

  program->main_menu = malloc(sizeof(WIN));
  program->main_menu->y = (program->max_y * 30) / 100;
  program->main_menu->x = (program->max_x * 30) / 100;
  program->main_menu->win = newwin(program->main_menu->y, program->main_menu->x, (program->max_y - program->main_menu->y) / 2, (program->max_x - program->main_menu->x) / 2);
  box(program->main_menu->win, 0, 0);
  keypad(program->main_menu->win, true);
  wrefresh(program->main_menu->win);
  
  char *menu_options[] = { "Start a new game", "Start a game from position", "Credits", "Exit" };
  int option = 0;
  draw_options(program, menu_options, option);
  while (true) {
    switch(wgetch(program->main_menu->win)) {
      case KEY_UP:
      case KEY_RIGHT: {
        if (option == 0) {
          option = 3;
        } else {
          option--;
        }
        draw_options(program, menu_options, option);
        break;
      }
      case KEY_DOWN:
      case KEY_LEFT: {
        if (option == 3) {
          option = 0;
        } else {
          option++;
        }
        draw_options(program, menu_options, option);
        break;
      }
      case 'q':
      case 'Q': {
        finish(program);
        break;
      }
      case ENTER: {
        assert(false); // not implemented
        break;
      }
      default:
        break;
    }
  }

  endwin();
  return 0;
}
