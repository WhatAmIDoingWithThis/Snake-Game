#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <thread>

#include "GameBoard.h"

using namespace std;
using namespace std::chrono;

//Function Pre-Declaration
int makeFrame(GameBoard*);
int kill();
void calculateSleep(duration<double>);
void listenForInput(GameBoard*);

//Static Variables
static int MovesPerSecond = 3;

//Thread check
bool running = true;

int main() {
	//Welcome Message
	cout << "SNAKE GAME!" << endl;
	cout << "Press any key to start..." << endl;
	_getch();

	//Generate a new GameBoard object
	GameBoard* board = new GameBoard();

	//Create movement thread
	thread inputThread(listenForInput, board);

	//Game Loop
	int i = 0;
	while (true) {
		auto beg = high_resolution_clock::now();

		switch (makeFrame(board)) {
		case -1:
			//tell input thread to stop
			running = false;
			int ret = kill();
			inputThread.join();
			return ret;
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

//Function that listens for input, meant to be run in a separate thread
void listenForInput(GameBoard* board) {
	while (running) {
		int dir = _getch();
		switch (dir) {
		case 72:
		case (int)'w':
			board->setDirection(1);
			break;
		case 77:
		case (int)'d':
			board->setDirection(2);
			break;
		case 80:
		case (int)'s':
			board->setDirection(3);
			break;
		case 75:
		case (int)'a':
			board->setDirection(4);
			break;
		}
	}
}