#include <iostream>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <thread>
#include <iomanip>

#include "GameBoard.h"

using namespace std;
using namespace std::chrono;

//Function Pre-Declaration
int makeFrame(GameBoard*);
int kill();
void calculateSleep(duration<double>);
void listenForInput(GameBoard*);

//Static Variables
int MovesPerSecond = 3;

//Thread check
bool running = true;

int main() {
	//Beginning values
	int w = 10, h = 10;
	MovesPerSecond = 3;

	//Welcome Message
MainMenu:
	system("cls");
	cout << "SNAKE GAME!" << endl;
	cout << "Press any key to start...  ... or 's' for settings" << endl;
	if (_getch() == 's') {
	Options:
		system("cls");
		cout << left;
		cout << setw(10) << "Option"
			<< "|" << setw(20) << "Description"
			<< "|" << setw(15) << "Current Value" << endl;
		cout << string(45, '-') << endl;
		cout << setw(10) << "1"
			<< "|" << setw(20) << "Moves Per Second"
			<< "|" << setw(15) << MovesPerSecond << endl;
		cout << setw(10) << "2"
			<< "|" << setw(20) << "Board Width"
			<< "|" << setw(15) << w << endl;
		cout << setw(10) << "3"
			<< "|" << setw(20) << "Board Height"
			<< "|" << setw(15) << h << endl;
		cout << string(45, '-') << endl;
		cout << endl;
		cout << "Enter the number of the option you would like to change" << endl;
		cout << "Press 'q' to go back to the main menu" << endl;
		switch (_getch()) {
		case '1':
			cout << "Moves Per Second: ";
			cin >> MovesPerSecond;
			break;
		case '2':
			cout << "Board Width: ";
			cin >> w;
			break;
		case '3':
			cout << "Board Height: ";
			cin >> h;
			break;
		case 'q':
			goto MainMenu;
		}
		goto Options;
	}

	//Generate a new GameBoard object
	GameBoard* board = new GameBoard(w, h);

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
			delete board;
			goto MainMenu;
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
	cout << "Press any key to return to the main menu" << endl;
	_getch();
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