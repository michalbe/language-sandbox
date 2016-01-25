#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  initscr();
  noecho();
  curs_set(FALSE);

  sleep(1);

  endwin(); // Restore normal terminal behavior
}
