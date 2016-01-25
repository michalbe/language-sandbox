#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

// Game config
#define WIDTH 40
#define HEIGHT 20

struct Point {
  int x;
  int y;
};

struct Snake {
   char          direction[10];
   int           length;
   struct Point  elements[100];
};

void createSnake(struct Snake *snake);
void drawBoard();

int main(int argc, char *argv[]) {
  struct Snake snake;

  // ncurses init stuff
  initscr();
  noecho();
  curs_set(FALSE);
  clear();

  // draw the board here
  drawBoard();

  refresh();
  sleep(1);
  endwin();
}

void createSnake(struct Snake *snake) {
  int i = snake->length;

}

void drawBoard() {
  int i = 0, j = 0;
  for (i=0; i < WIDTH; i++) {
    for (j=0; j < HEIGHT; j++) {
      if (
        (j == 0 | j == HEIGHT - 1) |
        (i == 0 | i == WIDTH - 1)) {
        mvprintw(j, i, "#");
      }
    }
  }
}
