import pygame
import sys

pygame.init()

# Configuration
width = 500
height = 500
screen = pygame.display.set_mode((width, height))
cellSize = 15;
cellsX = round(width/cellSize);
cellsY = round(height/cellSize);

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

def initGame():
    snake = SNAKE()
    snake.direction = 'right'
    snake.create()
    score = 0


initGame()

# main game loop
while (True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit(); sys.exit();

    # fill screen with default background color
    screen.fill(bgColor);

    #draw single rectangle
    pygame.draw.rect(screen, color, (0, 0, cellSize, cellSize), 0)
    pygame.display.update()