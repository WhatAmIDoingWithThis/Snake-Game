#include "Snake.h"

Snake::Snake(int x, int y)
{
	length = 1;
	bod temp;
	temp.x = x;
	temp.y = y;
	bodyPieces.push_back(temp);
}

void Snake::move(int x, int y)
{
	bod temp;
	temp.x = x;
	temp.y = y;
	bodyPieces.push_front(temp);
	bodyPieces.pop_back();
}