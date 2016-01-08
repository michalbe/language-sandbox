from sys import stdout
from time import sleep

def main():
    canvasWidth = 500;
    canvasHeight = 500;
    cellSize = 15;
    cellsX = int(round(canvasWidth/cellSize));
    cellsY = int(round(canvasHeight/cellSize));

    for i in range(0, cellsX):
        stdout.write('\n')
        for j in range(0, cellsY):
            stdout.write('*')
main()
