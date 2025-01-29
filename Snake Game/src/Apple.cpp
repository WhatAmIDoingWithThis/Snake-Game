#include "Apple.h"
#include <stdlib.h>

Apple::Apple(int width, int height)
{
	generatePosition(width, height);
};

void Apple::generatePosition(int width, int height)
{
	x = rand() % width + 1;
	y = rand() % height + 1;
}
