#include <list>

class Snake
{

public:
	struct bod {
		int x;
		int y;
	};
	Snake(int, int);
	void move(int, int, bool = false);
	std::list<bod> bodyPieces;
	int length;
};
