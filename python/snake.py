import pygame
import sys
import copy

pygame.init()

# Configuration
width = 500
height = 500
screen = pygame.display.set_mode((width, height))
cellSize = 15;
cellsX = round(width/cellSize);
cellsY = round(height/cellSize);
snake = None

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

    def render(self):
        for element in snake.elements:
            draw(element)

    def move(self):
        elementToMove = copy.deepcopy(self.elements)
        elementToMove = elementToMove[0]
        if self.direction == 'right':
            elementToMove['x'] = elementToMove.get('x') + 1

        self.elements.pop()
        self.elements.insert(0, elementToMove)

def initGame():
    global snake
    snake = SNAKE()
    snake.direction = 'right'
    snake.create()
    score = 0


def draw(element):
    pygame.draw.rect(screen, color, (element.get('x') * cellSize, element.get('y') * cellSize, cellSize, cellSize), 0)

def render():
    snake.move()
    snake.render()

initGame()

# main game loop
while (True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit(); sys.exit();

    # fill screen with default background color
    screen.fill(bgColor);

    #draw single rectangle
    render()
    pygame.display.update()
