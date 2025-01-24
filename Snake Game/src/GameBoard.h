#pragma once

#include <list>
#include "Snake.h"
#include "Apple.h"

class GameBoard
{

public:

	//Constructors
	GameBoard(int);
	GameBoard(int, int);

	//Variables
	int height;
	int width;

	//Board Access
	int computeBoard();
	void displayBoard();

private:

	//Variables
	int** board;
	Snake* snake;
	Apple* apple;

	//Constructor Methods
	void initBoard(int**, int, int);
};

