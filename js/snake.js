//Snake game
// Michał Budzyński
// Language sandbox Javascript example

var GAME = function() {
	// config & variables
	var canvas = document.getElementById('canvas');
	var ctx = canvas.getContext('2d');
	var canvasWidth = canvas.width;
	var canvasHeight = canvas.height;
	var cellSize = 15;
	var cellsX = Math.round(canvasWidth/cellSize);
	var cellsY = Math.round(canvasHeight/cellSize);
	var score;
	var gameLoop;

	var SNAKE = {
		elements: [],
		direction: 'right',
		length: 5,
		create: function(){
			this.elements = [];
			var i = this.length;
			while(i--) {
				this.elements.push({x: i, y:0});
			}
		},
		collidesWith: function(element){
			for(var i = 0; i < this.elements.length; i++) {
				if(
					this.elements[i].x == element.x &&
					this.elements[i].y == element.y
				) {
					return true;
				}
			}
			return false;
		}
	};

	var FOOD = {
		position: {},
		create: function(){
			this.position = {
				x: Math.round(Math.random()*(canvasWidth - cellSize)/cellSize),
				y: Math.round(Math.random()*(canvasHeight - cellSize)/cellSize)
			}
		}
	};

	var init = function() {
		SNAKE.direction = 'right';
		SNAKE.create();
		FOOD.create();
		score = 0;

		clearInterval(gameLoop);
		gameLoop = setInterval(render, 260);
	}

	//Lets paint the snake now
	function render() {
		// clear the canvas
		canvas.width = canvas.width;

		// copy the tail of the snake, this is the easiest way to do it in JS
		var elementToMove = JSON.parse(JSON.stringify(SNAKE.elements[0]));
		switch(SNAKE.direction) {
			case 'right':
				elementToMove.x++;
				break;
			case 'left':
				elementToMove.x--;
				break;
			case 'up':
				elementToMove.y--;
				break;
			case 'down':
				elementToMove.y++;
				break;
		};

		// game over conditions
		if(
			elementToMove.x === -1 ||
			elementToMove.x === cellsX ||
			elementToMove.y === -1 ||
			elementToMove.y === cellsY ||
			SNAKE.collidesWith(elementToMove)
		) {
			//restart game
			alert("Game Over!\nScore: " + score);
			init();
			return;
		}

		SNAKE.elements.unshift(elementToMove);

		if(
			elementToMove.x === FOOD.position.x &&
			elementToMove.y === FOOD.position.y
		) {
			// snake ate food
			score++;
			FOOD.create();
		} else {
			// snake didn't
			SNAKE.elements.pop();
		}

		SNAKE.elements.forEach(function(element){
			draw(element);
		});
		draw(FOOD.position);
		ctx.fillText('SCORE: ' + score, 5, canvasHeight - 5);
	}

	function draw(element) {
		ctx.fillRect(
			element.x * cellSize,
			element.y * cellSize,
			cellSize,
			cellSize
		);
		ctx.strokeStyle = 'white';
		ctx.strokeRect(
			element.x * cellSize,
			element.y * cellSize,
			cellSize,
			cellSize
		);
	}

	document.addEventListener('keydown', function(e) {
		var key = e.which;
		if(key === 37 && SNAKE.direction !== 'right') SNAKE.direction = 'left';
		else if(key === 38 && SNAKE.direction !== 'down') SNAKE.direction = 'up';
		else if(key === 39 && SNAKE.direction !== 'left') SNAKE.direction = 'right';
		else if(key === 40 && SNAKE.direction !== 'up') SNAKE.direction = 'down';
	});

	init();
};

GAME();
