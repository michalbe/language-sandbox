#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

// Game config
#define WIDTH 40
#define HEIGHT 20
#define PIXEL "#"

#define INITIAL_SNAKE_LENGTH 5
#define INITIAL_SNAKE_MARGIN 2

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
void drawSnake(struct Snake *snake);
void draw(struct Point *point);
void drawBoard();

int main(int argc, char *argv[]) {
  struct Snake snake;
  int c;
  // ncurses init stuff
  initscr();
  noecho();
  curs_set(FALSE);
  clear();

  // draw the board here
  drawBoard();

  snake.length = INITIAL_SNAKE_LENGTH;
  createSnake(&snake);
  drawSnake(&snake);

  refresh();
  while(1) {
    c = getch();
    mvprintw(5, 5, "%d", c);
		switch(c) {
      case 65: //UP
				mvprintw(5, 5, "UP");
				break;
			case 66: // DOWN
				mvprintw(5, 5, "DW");
				break;
      case 68: // LEFT
				mvprintw(5, 5, "LF");
				break;
      case 67: // RIGHT
				mvprintw(5, 5, "RG");
				break;
		}
	}
  endwin();
}

void createSnake(struct Snake *snake) {
  int length = snake->length;
  for (int i = 0; i < length; i++) {
    snake->elements[i].x = i + INITIAL_SNAKE_MARGIN;
    snake->elements[i].y = INITIAL_SNAKE_MARGIN;
  }
}

void drawSnake(struct Snake *snake) {
  for (int i=0; i < snake->length; i++) {
    draw(&snake->elements[i]);
  }
}
void draw(struct Point *point) {
  mvprintw(point->y, point->x, PIXEL);
}

void drawBoard() {
  int i = 0;
  int j = 0;

  for (i=0; i < WIDTH; i++) {
    for (j=0; j < HEIGHT; j++) {
      if (
        (j == 0 | j == HEIGHT - 1) |
        (i == 0 | i == WIDTH - 1)) {
        mvprintw(j, i, PIXEL);
      }
    }
  }
}
