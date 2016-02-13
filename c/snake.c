#include <ncurses.h>
#include <unistd.h>
#include <string.h>

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

struct Point {
  int x;
  int y;
};

struct Snake {
   directions    direction;
   int           length;
   struct Point  elements[100];
};


void createSnake(struct Snake *snake);
void drawSnake(struct Snake *snake);
void draw(struct Point *point);
void drawBoard();
void redrawAll(struct Snake *snake);

int main(int argc, char *argv[]) {
  struct Snake snake;
  int c;
  // ncurses init stuff
  initscr();
  noecho();
  curs_set(FALSE);

  snake.length = INITIAL_SNAKE_LENGTH;
  createSnake(&snake);

  struct Point elementToMove = snake.elements[0];

  elementToMove.x = 8;
  elementToMove.y = 8;
  while(1) {
    // main loop starts here
    redrawAll(&snake);

    switch(snake.direction) {
      case up:
        elementToMove.y--;
				break;
			case down:
        elementToMove.y++;
				break;
      case left:
        elementToMove.x--;
				break;
      case right:
        elementToMove.x++;
				break;
    }

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

    sleep(1/60);
	}

  endwin();
}

void createSnake(struct Snake *snake) {
  int length = snake->length;
  for (int i = 0; i < length; i++) {
    snake->elements[i].x = i + INITIAL_SNAKE_MARGIN;
    snake->elements[i].y = INITIAL_SNAKE_MARGIN;
  }

  snake->direction = right;
}

void drawSnake(struct Snake *snake) {
  for (int i=0; i < snake->length; i++) {
    draw(&snake->elements[i]);
  }
}

void draw(struct Point *point) {
  mvprintw(point->y, point->x, PIXEL);
}

void redrawAll(struct Snake *snake) {
  clear();
  drawBoard();
  drawSnake(snake);
  refresh();
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
