#pragma once

#include <list>
#include "Snake.h"
#include "Apple.h"

class GameBoard
{

public:

	//Constructors
	GameBoard(int = 10);
	GameBoard(int, int);

	//Destructor
	~GameBoard();

	//Variables
	int height;
	int width;
	void setDirection(int);

	//Board Access
	int computeBoard();
	void displayBoard();

private:

	//Variables
	int direction;
	int** board;
	Snake* snake;
	Apple* apple;

	//Constructor Methods
	void initBoard(int**, int, int);
};

