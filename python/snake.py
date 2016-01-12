import pygame
import sys
import copy
import random

pygame.init()

# Configuration
width = 500
height = 500
screen = pygame.display.set_mode((width, height))
cellSize = 15;
cellsX = round(width/cellSize);
cellsY = round(height/cellSize);
snake = None
food = None
gameloop = True
fps = 20

# set default drawing colors
color = (0,0,0)
bgColor = (255,255,255)


class SNAKE:
    def __init__(self):
        self.elements = []
        self.direction = 'right'
        self.length = 5

    def create(self):
        self.elements = []
        i = self.length
        while i != 0:
            self.elements.append({'x': i, 'y':0})
            i -= 1
    def collidesWith(self, otherElement):
			for element in self.elements:
				if (element['x'] == otherElement['x'] and
					element['y'] == otherElement['y']):
					return True
			return False;

    def render(self):
        for element in self.elements:
            draw(element)

    def move(self):
        global gameloop
        elementToMove = copy.deepcopy(self.elements)
        elementToMove = elementToMove[0]
        if self.direction == 'right':
            elementToMove['x'] = elementToMove['x'] + 1
        elif self.direction == 'left':
            elementToMove['x'] = elementToMove['x'] - 1
        elif self.direction == 'down':
            elementToMove['y'] = elementToMove['y'] + 1
        elif self.direction == 'up':
            elementToMove['y'] = elementToMove['y'] - 1

        if (elementToMove['x'] == -1 or
            elementToMove['x'] == cellsX or
            elementToMove['y'] == -1 or
            elementToMove['y'] == cellsY or
            self.collidesWith(elementToMove)):
			# restart game
			gameloop = False

        self.elements.pop()
        self.elements.insert(0, elementToMove)

class FOOD:
    def __init__(self):
        self.position = None

    def create(self):
        self.position = {
            'x': random.randrange(0, (width - cellSize)/cellSize, 1),
            'y': random.randrange(0, (height - cellSize)/cellSize, 1)
        }

    def render(self):
        draw(self.position)

def initGame():
    global snake, food
    snake = SNAKE()
    snake.direction = 'right'
    snake.create()
    food = FOOD()
    food.create()
    score = 0


def draw(element):
    pygame.draw.rect(
        screen,
        color,
        (
            element['x'] * cellSize,
            element['y'] * cellSize,
            cellSize,
            cellSize
        ),
        0
    )

def render():
    snake.move()
    snake.render()
    food.render()

initGame()

# main game loop
while (True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit(); sys.exit();
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT and snake.direction != 'right':
                snake.direction = 'left'
            if event.key == pygame.K_RIGHT and snake.direction != 'left':
                snake.direction = 'right'
            if event.key == pygame.K_DOWN and snake.direction != 'up':
                snake.direction = 'down'
            if event.key == pygame.K_UP and snake.direction != 'down':
                snake.direction = 'up'

    # fill screen with default background color
    screen.fill(bgColor);

    #draw single rectangle
    if gameloop:
        render()
        pygame.display.update()
        pygame.time.wait(1000/fps)
