import pygame
import sys

pygame.init()

#setup the screen
screen = pygame.display.set_mode((500, 500))

print pygame.version.ver

# set default drawing colors
color = (0,0,0)
bgColor = (255,255,255)

#main game loop
while (True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit(); sys.exit();

    # fill screen with default background color
    screen.fill(bgColor);

    #draw single rectangle
    pygame.draw.rect(screen, color, (0,0,15,15), 0)
    pygame.display.update()
