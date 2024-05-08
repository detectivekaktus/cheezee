#include "backend.h"
#include "cheezee.h"
#include "frontend.h"
#include "main.h"

void finish(Program *program) {
  if (program->main_menu != NULL) DESTROY_WINDOW(program->main_menu);
  if (program->board != NULL) DESTROY_WINDOW(program->board);
  endwin();

  free(program);
  exit(0);
}

void draw_options(const Program *program, char **options, int option) {
  for (int i = 0; i < 4; i++) {
    if (option == i) {
      wattron(program->main_menu->win, A_REVERSE);
      mvwaddstr(program->main_menu->win, getcury(program->main_menu->win) + program->main_menu->y * 0.2, (program->main_menu->x - strlen(options[i])) / 2, options[i]);
      wattroff(program->main_menu->win, A_REVERSE);
    } else {
      mvwaddstr(program->main_menu->win, getcury(program->main_menu->win) + program->main_menu->y * 0.2, (program->main_menu->x - strlen(options[i])) / 2, options[i]);
    }
  }
  wmove(program->main_menu->win, 0, 0);
  wrefresh(program->main_menu->win);
}

int main(void) {
  setlocale(LC_ALL, "");
  Program *program = malloc(sizeof(Program));

  initscr();
  cbreak();
  noecho();
  getmaxyx(stdscr, program->y, program->x);
  if (!has_colors() || !can_change_color()) CRASH("Your terminal does not support colors.\n");
  if (program->y < TILE_HEIGHT * 8 + 2 || program->x < TILE_WIDTH * 8 + 2) CRASH("Your viewport must be at least %dx%d to run this program. Try to zoom out or buy a new monitor.\n", TILE_HEIGHT * 8 + 2, TILE_WIDTH * 8 + 2);
  init_colors();

  WIN *main_menu;
  CREATE_CENTERED_WINDOW(program, main_menu, program->y * 0.5, program->x * 0.5);
  program->main_menu = main_menu;
  wborder(program->main_menu->win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  keypad(program->main_menu->win, true);
  wrefresh(program->main_menu->win);
  
  char *menu_options[] = { "Start a new game", "Start a game from position", "Credits", "Exit" };
  int option = 0;
  draw_options(program, menu_options, option);
  while (true) {
    switch (wgetch(program->main_menu->win)) {
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
        switch (option) {
          case NEW_GAME: {
            clear();
            refresh();
            play(program);
            clear();
            refresh();
            draw_options(program, menu_options, option);
            break;
          }
          case FEN_POS: {
            ASSERT(false, "not implemented.\n");
            break;
          }
          case CREDITS: {
            WIN *credits;
            WIN *credits_text;
            CREATE_CENTERED_WINDOW(program, credits, program->y * 0.6, program->x * 0.5);
            box(credits->win, 0, 0);
            CREATE_WINDOW(credits_text, credits->y * 0.8, credits->x * 0.8, credits->start_y + 3, credits->start_x + 5);
            mvwprintw(credits_text->win, 0, 0, "Hi there!");
            mvwprintw(credits_text->win, getcury(credits_text->win) + 2, 0, "I'm Artiom Astashonak, a third year high-school student, who's interested in computer science. I made this project to practice my C programming skills, as well as to learn ncurses library.");
            mvwprintw(credits_text->win, getcury(credits_text->win)+ 2, 0, "You can find the source code of this application at: ");
            wattron(credits_text->win, A_UNDERLINE);
            wprintw(credits_text->win, "https://github.com/detectivekaktus/cheezee");
            wattroff(credits_text->win, A_UNDERLINE);
            wrefresh(credits->win);
            wrefresh(credits_text->win);
            
            int key;
            do {
              key = wgetch(credits->win);
            } while (key != ESCAPE && (key != 'Q' && key != 'q'));
            clear();
            DESTROY_WINDOW(credits);
            DESTROY_WINDOW(credits_text);
            refresh();
            draw_options(program, menu_options, option);
            break;
          }
          case EXIT: {
            finish(program);
            break;
          }
          default:
            ASSERT(false, "unreachable.\n");
            break;
        }
        break;
      }
      default:
        break;
    }
  }

  endwin();
  return 0;
}
