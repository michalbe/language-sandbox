#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "linked-point/linked-point.h"

#define DELAY 30000

// Game config
#define WIDTH 40
#define HEIGHT 20
#define PIXEL "#"

#define INITIAL_SNAKE_LENGTH 5
#define INITIAL_SNAKE_MARGIN 2

typedef enum {
  up,
  right,
  left,
  down
} directions;

struct Snake {
   directions    direction;
   int           length;
   struct Point  *elements;
};


void createSnake(struct Snake *snake);
void drawSnake(struct Snake *snake);
void draw(struct Point *point);
void drawBoard();
void redrawAll(struct Snake *snake);

int frame = 0;
int main(int argc, char *argv[]) {
  struct Snake snake;
  int c, x, y;
  // ncurses init stuff
  initscr();
  noecho();
  curs_set(FALSE);

  snake.length = INITIAL_SNAKE_LENGTH;
  createSnake(&snake);

  while(1) {
    // get the last points coords
    last(&snake.elements, &x, &y);

    // main loop starts here
    redrawAll(&snake);

    switch(snake.direction) {
      case up:
        y--;
				break;
			case down:
        y++;
				break;
      case left:
        x--;
				break;
      case right:
        x++;
				break;
    }

    // add the new elements with modified coords based on the last one
    push(&snake.elements, x, y);

    // remove the first element
    shift(&snake.elements, &x, &y);

    // c = getch();
    // mvprintw(5, 5, "%d", c);
		// switch(c) {
    //   case 65: //UP
		// 		mvprintw(5, 5, "UP");
		// 		break;
		// 	case 66: // DOWN
		// 		mvprintw(5, 5, "DW");
		// 		break;
    //   case 68: // LEFT
		// 		mvprintw(5, 5, "LF");
		// 		break;
    //   case 67: // RIGHT
		// 		mvprintw(5, 5, "RG");
		// 		break;
		// }

    sleep(1);
	}

  endwin();
}

void createSnake(struct Snake *snake) {
  snake->elements = NULL;
  snake->direction = right;

  int length = snake->length;
  for (int i = 0; i < length; i++) {
    push(&snake->elements, i + INITIAL_SNAKE_MARGIN, INITIAL_SNAKE_MARGIN);
  }
}

void drawSnake(struct Snake *snake) {
  struct Point *current = snake->elements;
  int iters = 0;
  while(current != NULL) {
    draw(current);
    current = current->next;
  }
}

void draw(struct Point *point) {
  mvprintw(point->y, point->x, PIXEL);
}

void redrawAll(struct Snake *snake) {
  clear();
  drawBoard();
  drawSnake(snake);
  mvprintw(20, 3, "%d", frame);
  refresh();

  frame++;
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
