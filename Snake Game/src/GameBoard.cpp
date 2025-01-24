#include "GameBoard.h"

#include <iostream>

using namespace std;

static char WallChar = '#';
static char EmptyChar = ' ';
static char SnakeChar = 'O';
static char AppleChar = 'X';
static char VerticalChar = '|';
static char HorizontalChar = '-';
static char CornerOneChar = '/';
static char CornerTwoChar = '\\';

//Default Constructor, sets for a square board
GameBoard::GameBoard(int size = 10) {
	width = size;
	height = size;
	
	//Allocate memory for the board
	board = new int*[size + 2];
	for (int i = 0; i < size + 2; i++) {
		board[i] = new int[size + 2];
	};
	initBoard(board, size, size);

	//Generate a new Snake object in the middle of the board
	snake = new Snake(size/2, size/2);

	//Generate a new Apple object
	apple = new Apple(size, size);
};

//Constructor for a board of custom sizing
GameBoard::GameBoard(int w, int h) {
	width = w;
	height = h;
	
	//Allocate memory for the board
	board = new int*[w + 2];
	for (int i = 0; i < w + 2; i++) {
		board[i] = new int[h + 2];
	};
	initBoard(board, w, h);

	//Generate a new Snake object in the middle of the board
	snake = new Snake(w/2, h/2);

	//Generate a new Apple object
	apple = new Apple(w, h);
};

//This method initializes the board. Basically sets the boundaries, and the middle to 0
void GameBoard::initBoard(int** board, int width, int height) {
	for (int curX = 0; curX < width + 2; curX++) {
		for (int curY = 0; curY < height + 2; curY++) {
			if (curX == 0 || curX == width + 1 || curY == 0 || curY == height + 1) {
				board[curX][curY] = 1;
			}
			else {
				board[curX][curY] = 0;
			}
		}
	}
};

//This method prints the board to the console
void GameBoard::displayBoard() {
	for (int curX = 0; curX < width + 2; curX++) {
		for (int curY = 0; curY < height + 2; curY++) {
			switch (board[curX][curY]) {
			case 0:
				cout << EmptyChar;
				break;
			case 1:
				cout << WallChar;
				break;
			case 2:
				cout << SnakeChar;
				break;
			case 3:
				cout << AppleChar;
				break;
			case 4:
				cout << VerticalChar;
				break;
			case 5:
				cout << HorizontalChar;
				break;
			case 6:
				cout << CornerOneChar;
				break;
			case 7:
				cout << CornerTwoChar;
				break;
			}
		}
		cout << endl;
	}
};

//This method computes the position of the snake and the apple on the board
int GameBoard::computeBoard() {
	//Clear the board
	initBoard(board, width, height);

	//Set the snake on the board
	for (const Snake::bod& temp : snake->bodyPieces) {
		if (board[temp.x][temp.y] != 0) {
			return -1;
		}
		board[temp.x][temp.y] = 2;
	};

	//Set the apple on the board
	board[apple->x][apple->y] = 3;
	if(board[apple->x][apple->y] == 2) {
		return 1;
	};

	return 0;
};