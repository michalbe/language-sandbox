#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "linked-point/linked-point.h"

#define DELAY 100000

// Game config
#define WIDTH 40
#define HEIGHT 20
#define PIXEL "#"
#define FOOD_PIXEL "@"

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
void redrawAll(struct Snake *snake, struct Point *food);
int readInput(void);
int collides(struct Point *snake, int x, int y);
int randRange(int min, int max);
void createFood(struct Point *food);
void drawFood(struct Point *food);

int score = 0;
int main(int argc, char *argv[]) {
  struct Snake snake;
  struct Point food;
  int c, x, y;


  // ncurses init stuff
  initscr();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(FALSE);

  srand(time(NULL));

  snake.length = INITIAL_SNAKE_LENGTH;
  createSnake(&snake);
  createFood(&food);

  while(1) {
    if (readInput()) {
      switch(getch()) {
        case 65: //UP
          if (snake.direction != down)
            snake.direction = up;
          break;
        case 66: // DOWN
          if (snake.direction != up)
            snake.direction = down;
          break;
        case 68: // LEFT
          if (snake.direction != right)
            snake.direction = left;
          break;
        case 67: // RIGHT
          if (snake.direction != left)
            snake.direction = right;
          break;
      }
    } else {
      // get the last points coords
      last(&snake.elements, &x, &y);

      // main loop starts here

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

      // Game over conditions
      if (
  			x == 0 ||
  			x >= WIDTH ||
  			y == 0 ||
  			y >= HEIGHT ||
        collides(snake.elements, x, y)
  		) {
        clear();
  		  mvprintw(0, 0, "GAME OVER\nSCORE: %d\n\n", score);
        refresh();
  			return 0;
  		}
      // add the new elements with modified coords based on the last one
      push(&snake.elements, x, y);

      if(
  			x == food.x &&
  			y == food.y
  		) {
        score++;
  			createFood(&food);
  		} else {
        // remove the first element
        shift(&snake.elements, &x, &y);
      }
      redrawAll(&snake, &food);
      usleep(DELAY);
    }
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

void redrawAll(struct Snake *snake, struct Point *food) {
  clear();
  drawBoard();
  drawSnake(snake);
  drawFood(food);
  mvprintw(20, 3, "SCORE: %d", score);
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

int readInput(void) {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int collides(struct Point *snake, int x, int y) {
  while (snake != NULL) {
    if(
      snake->x == x &&
      snake->y == y
    ) {
      return 1;
    }
    snake = snake->next;
  }
  return 0;
}

void createFood(struct Point *food) {
  food->x = randRange(1, WIDTH-2);
  food->y = randRange(1, HEIGHT-2);
}

void drawFood(struct Point *food) {
  mvprintw(food->y, food->x, FOOD_PIXEL);
}

int randRange(int min, int max) {
  rand();
  int r;
  const int range = 1 + max - min;
  const int buckets = RAND_MAX / range;
  const int limit = buckets * range;

  /* Create equal size buckets all in a row, then fire randomly towards
   * the buckets until you land in one of them. All buckets are equally
   * likely. If you land off the end of the line of buckets, try again. */
  do {
    r = rand();
  } while (r >= limit);

  return min + (r / buckets);
}
