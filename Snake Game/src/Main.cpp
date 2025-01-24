#include <Windows.h>
#include <iostream>
#include <forward_list>;
#include <chrono>

using namespace std;
using namespace std::chrono;

class GameBoard {
public:
	struct Apple {
		int x;
		int y;
	};

	int height;
	int width;
	Apple apple;
	GameBoard(int height = 20, int width = 20) {
		this->height = height;
		this->width = width;
		newApple();
	};
	bool appleEaten(int checkX, int checkY) {
		if (checkX == apple.x && checkY == apple.y) {
			newApple();
			return true;
		}
		return false;
	}
	void newApple() {
		apple.x = rand() % width;
		apple.y = rand() % height;
	}
};

class Snake {
public:
	struct SnakeBod {
		int x;
		int y;
	};

	int headX;
	int headY;
	forward_list<SnakeBod> bodyList;

	Snake(int startX = 0, int startY = 0) {
		this->headX = startX;
		this->headY = startY;
		bodyList.clear();
	}
};

int calculateSleepTime(int time) {
	//60fps way too fast. Maybe 10?
	cout << time;
	return (1000/5) - time;
}

int checkForMovement(Snake* snake, int movement) {

	if ((GetAsyncKeyState(VK_LEFT) & 0b1) || (GetAsyncKeyState(0x41) & 0b1)) movement = 0;
	else if ((GetAsyncKeyState(VK_UP) & 0b1) || (GetAsyncKeyState(0x57) & 0b1)) movement = 1;
	else if ((GetAsyncKeyState(VK_RIGHT) & 0b1) || (GetAsyncKeyState(0x44) & 0b1)) movement = 2;
	else if ((GetAsyncKeyState(VK_DOWN) & 0b1) || (GetAsyncKeyState(0x53) & 0b1)) movement = 3;

	switch (movement) {
	case 0: snake->headX--; break;
	case 1: snake->headY--; break;
	case 2: snake->headX++; break;
	default: snake->headY++; break;
	}

	int prevX = snake->headX, prevY = snake->headY;
	for (Snake::SnakeBod bod : snake->bodyList) {
		int tempX = bod.x, tempY = bod.y;
		bod.x = prevX;
		bod.y = prevY;
		prevX = tempX;
		prevY = tempY;
		cout << "{ " << bod.x << ", " << bod.y << '}';
	}

	return movement;
}

int main() {

	static char wall = '#';
	static char apple = 'O';
	static char head = '%';
	static char bod = '=';

	cout << "Snake Game!\nPress Enter to begin\n";
	cin.get();

	bool gameRunning = true;
	bool headDrawn = false;
	bool appleDrawn = false;
	GameBoard* game = new GameBoard();
	Snake* snake = new Snake(game->width/2, game->height/2);
	int lastDirection = 0;
	while (gameRunning) {
		auto beg = high_resolution_clock::now();
		system("cls");
		headDrawn = false;
		appleDrawn = false;

		//print top wall
		for (int i = 0; i < game->width + 2; i++) {
			cout << wall;
		}
		cout << '\n';

		//Print rest of gameboard
		for (int curHeightPos = 0; curHeightPos < game->height; curHeightPos++) {
			cout << wall;
			for (int curWidthPos = 0; curWidthPos < game->width; curWidthPos++) {

				//Check if a snake body is there
				bool bodPos = false;
				for (Snake::SnakeBod bod : snake->bodyList) {
					if (bod.x == curWidthPos && bod.y == curHeightPos) bodPos = true;
				}
				if (bodPos) cout << bod;

				//Check if snake head is there
				else if (snake->headX == curWidthPos && snake->headY == curHeightPos) {
					cout << head;
					headDrawn = true;
				}

				//Check if apple is there
				else if (game->apple.x == curWidthPos && game->apple.y == curHeightPos) {
					cout << apple;
					appleDrawn = true;
				}

				//Empty space
				else cout << ' ';
			}
			cout << wall;
			cout << '\n';
		}

		//Print bottom wall
		for (int i = 0; i < game->width + 2; i++) {
			cout << wall;
		}
		cout << '\n';

		//Check for movement
		lastDirection = checkForMovement(snake, lastDirection);

		//Check death
		if (!headDrawn) gameRunning = false;

		//Check if apple was eaten
		if (!appleDrawn) {
			if(!snake->bodyList.empty()) snake->bodyList.push_front({ game->apple.x, game->apple.y });
			else {
			}
			game->newApple();
		}

		//Pause until next frame (60fps)
		auto end = high_resolution_clock::now();
		auto dur = duration_cast<milliseconds>(end - beg);
		Sleep(calculateSleepTime(dur.count()));
	}

	system("cls");
	cout << "YOU DIED";

	cin.get();
	return 0;
}