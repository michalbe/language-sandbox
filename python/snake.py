def main():
    canvasWidth = 500;
    canvasHeight = 500;
    cellSize = 15;
    cellsX = int(round(canvasWidth/cellSize));
    cellsY = int(round(canvasHeight/cellSize));

    for i in range(0, cellsX):
        print '\n',
        for j in range(0, cellsY):
            print '*',
main()
