#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>

#include "GameBoard.h"

using namespace std;
using namespace std::chrono;

//Function Pre-Declaration
int makeFrame(GameBoard*);
int kill();
void calculateSleep(duration<double>);

//Static Variables
static int MovesPerSecond = 10;

int main() {
	//Welcome Message
	cout << "SNAKE GAME!" << endl;
	cout << "Press any key to start..." << endl;
	_getch();

	//Generate a new GameBoard object
	GameBoard* board = new GameBoard(10);

	//Game Loop
	int i = 0;
	while (true) {
		auto beg = high_resolution_clock::now();

		switch (makeFrame(board)) {
		case -1:
			return kill();
		}

		auto end = high_resolution_clock::now();
		auto dur = duration_cast<milliseconds>(end - beg);
		calculateSleep(dur);
	}

	//Display board
	board->computeBoard();
	board->displayBoard();

	return 0;
}

//Function that generates and displays each frame
int makeFrame(GameBoard* board) {
	system("cls");
	int temp = board->computeBoard();
	board->displayBoard();
	return temp;
}

//Function that kills the player
int kill() {
	system("cls");
	cout << "You died!" << endl;
	return 0;
}

//Function that calculates the sleep time
void calculateSleep(duration<double> dur) {
	if (dur.count() < 1000 / MovesPerSecond) {
		Sleep(1000 / MovesPerSecond - dur.count());
	}
}