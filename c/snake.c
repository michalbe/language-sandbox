#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

// Game config
#define WIDTH 40
#define HEIGHT 20

int main(int argc, char *argv[]) {
  int i = 0, j = 0;

  initscr();
  noecho();
  curs_set(FALSE);
  clear();

  for (i=0; i < WIDTH; i++) {
    for (j=0; j < HEIGHT; j++) {
      if (
        (j == 0 | j == HEIGHT - 1) |
        (i == 0 | i == WIDTH - 1)) {
        mvprintw(j, i, "#");
      }
    }
  }

  refresh();
  sleep(1);
  endwin();
}
