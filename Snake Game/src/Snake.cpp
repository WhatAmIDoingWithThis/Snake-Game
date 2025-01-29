#include "Snake.h"

//Creates a new snake object with a single body piece at the specified location
Snake::Snake(int x, int y)
{
	length = 1;
	bod temp;
	temp.x = x;
	temp.y = y;
	bodyPieces.push_back(temp);
}

//Moves the snake in the specified direction
void Snake::move(int x, int y, bool appleEaten)
{
	bod temp = { bodyPieces.front().x, bodyPieces.front().y };
	temp.x = x;
	temp.y = y;
	bodyPieces.push_front(temp);
	if(!appleEaten) bodyPieces.pop_back();
}