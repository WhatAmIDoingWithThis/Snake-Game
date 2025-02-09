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
static char Error = 'E';

//Default Constructor, sets for a square board
GameBoard::GameBoard(int size, HANDLE console) {
	width = size;
	height = size;
	direction = 1;
	hConsole = console;
	
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
GameBoard::GameBoard(int w, int h, HANDLE console) {
	width = w;
	height = h;
	direction = 1;
	hConsole = console;
	
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

//Destructor
GameBoard::~GameBoard() {
	for (int i = 0; i < width + 2; i++) {
		delete[] board[i];
	};
	delete[] board;
};

//This method sets the direction of the snake
void GameBoard::setDirection(int dir) {
	direction = dir;
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
				//No color change needed
				cout << EmptyChar;
				break;
			case 1:
				//Set color white
				SetConsoleTextAttribute(hConsole, 0x0F);
				cout << WallChar;
				break;
			case 2:
				//Set color green
				SetConsoleTextAttribute(hConsole, 0x0A);
				cout << SnakeChar;
				break;
			case 3:
				//Set color red
				SetConsoleTextAttribute(hConsole, 0x0C);
				cout << AppleChar;
				break;
			case 4:
				//Set color green
				SetConsoleTextAttribute(hConsole, 0x0A);
				cout << VerticalChar;
				break;
			case 5:
				//Set color green
				SetConsoleTextAttribute(hConsole, 0x0A);
				cout << HorizontalChar;
				break;
			case 6:
				//Set color green
				SetConsoleTextAttribute(hConsole, 0x0A);
				cout << CornerOneChar;
				break;
			case 7:
				//Set color green
				SetConsoleTextAttribute(hConsole, 0x0A);
				cout << CornerTwoChar;
				break;
			default:
				//Set color blue
				SetConsoleTextAttribute(hConsole, 0x09);
				cout << Error;
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

	//Move the snake
	//1 = up, 2 = right, 3 = down, 4 = left
	int xHead = snake->bodyPieces.front().x;
	int yHead = snake->bodyPieces.front().y;
	bool appleEaten = false;
	if(xHead == apple->x && yHead == apple->y) {
		appleEaten = true;
		apple->generatePosition(width, height);
	};
	//Screwed up some code somewhere that determines x and y, but I'm just going to code around it here
	switch (direction) {
	case 1:
		snake->move(xHead - 1, yHead, appleEaten);
		break;
	case 2:
		snake->move(xHead, yHead + 1, appleEaten);
		break;
	case 3:
		snake->move(xHead + 1, yHead, appleEaten);
		break;
	case 4:
		snake->move(xHead, yHead - 1, appleEaten);
		break;
	}

	//Set the apple on the board
	board[apple->x][apple->y] = 3;
	if(board[apple->x][apple->y] == 2) {
		return 1;
	};

	//Set the snake on the board
	bool head = true;
	int prevX, prevY, nextX, nextY;
	for (auto currentBod = snake->bodyPieces.begin(); currentBod != snake->bodyPieces.end(); currentBod++) {
		//Check if the snake is out of bounds
		if(board[currentBod->x][currentBod->y] != 0 && board[currentBod->x][currentBod->y] != 3) {
			return -1;
		}
		//Draw head
		if(head) {
			head = false;
			board[currentBod->x][currentBod->y] = 2;
		}
		//Draw body
		else {
			//Get next
			auto nextBod = next(currentBod);
			if(nextBod == snake->bodyPieces.end()) {
				nextX = -1;
				nextY = -1;
			}
			else {
				nextX = nextBod->x;
				nextY = nextBod->y;
			}

			//Check direction of previous segment
			int prevDir;
			if (prevX > currentBod->x) prevDir = 3;			//Down
			else if (prevX < currentBod->x) prevDir = 1;	//Up
			else if (prevY > currentBod->y) prevDir = 2;	//Right
			else prevDir = 4;								//Left

			//Check direction of next segment
			int nextDir = 0;
			if (nextX != -1) {
				if (nextX > currentBod->x) nextDir = 3;		//Down
				else if (nextX < currentBod->x) nextDir = 1;//Up
				else if (nextY > currentBod->y) nextDir = 2;//Right
				else nextDir = 4;							//Left
			}

			//Vertical Body Segment
			if ((prevDir == 1 || prevDir == 3) && (nextDir == 1 || nextDir == 3 || nextDir == 0)) {
				board[currentBod->x][currentBod->y] = 4;
			}
			//Horizontal Body Segment
			else if ((prevDir == 2 || prevDir == 4) && (nextDir == 2 || nextDir == 4 || nextDir == 0)) {
				board[currentBod->x][currentBod->y] = 5;
			}
			//Moving right->up or down->left
			else if (
				(prevDir == 2 && nextDir == 3) || 
				(prevDir == 4 && nextDir == 1) ||
				(prevDir == 3 && nextDir == 2) ||
				(prevDir == 1 && nextDir == 4)
				) {
				board[currentBod->x][currentBod->y] = 6;
			}
			//Moving right->down or up->left
			else if (
				(prevDir == 3 && nextDir == 4) ||
				(prevDir == 1 && nextDir == 2) ||
				(prevDir == 2 && nextDir == 1) ||
				(prevDir == 4 && nextDir == 3)
				) {
				board[currentBod->x][currentBod->y] = 7;
			}
			else {
				board[currentBod->x][currentBod->y] = -1;
				cout << "Error: " << prevDir << " " << nextDir << endl;
			}
		}
		prevX = currentBod->x;
		prevY = currentBod->y;
	};

	return 0;
};