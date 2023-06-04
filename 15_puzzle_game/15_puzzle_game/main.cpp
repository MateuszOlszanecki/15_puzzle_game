#include"head.h"

string name;

int board[4][4];
int emptyPoss[2] = { 3,3 };

int shuffleCount = 80;

int pressCount;

int menuOption = 0;
bool menuShow = true;

bool playing;
bool startPressed = false;

bool noNewScore;

void gameplay() {
	removeCursor();
	noNewScore = false;
	pressCount = 0;
	emptyPoss[0] = 3;
	emptyPoss[1] = 3;
	makeBoard(board);
	shuffle(board, emptyPoss, shuffleCount);
	showBoard(board, emptyPoss);
	showScore(pressCount);
	cout << endl << "Press '0' to quit playing" << endl;
	playing = true;
	while (playing) {
		removeCursor();
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
				if (emptyPoss[0] < 3) {
					clear();
					pressCount++;
					moveCell(board, emptyPoss, 0);
					showBoard(board, emptyPoss);
					showScore(pressCount);
					playing = winCheck(board);
				}
				break;
			case 'a':
				if (emptyPoss[1] < 3) {
					clear();
					pressCount++;
					moveCell(board, emptyPoss, 1);
					showBoard(board, emptyPoss);
					showScore(pressCount);
					playing = winCheck(board);
				}
				break;
			case 's':
				if (emptyPoss[0] > 0) {
					clear();
					pressCount++;
					moveCell(board, emptyPoss, 2);
					showBoard(board, emptyPoss);
					showScore(pressCount);
					playing = winCheck(board);
				}
				break;
			case 'd':
				if (emptyPoss[1] > 0) {
					clear();
					pressCount++;
					moveCell(board, emptyPoss, 3);
					showBoard(board, emptyPoss);
					showScore(pressCount);
					playing = winCheck(board);
				}
				break;
			case '0':
				playing = false;
				noNewScore = true;
				break;
			}
		}
	}
	if (!noNewScore) {
		cin >> name;
		menuOption = 2;
		addToScoreboard(name, pressCount);
	}
	system("cls");
}

int main() {
	fontSize();
	fullScreen();

	removeCursor();
	loadScoreboard();
	while (menuShow) {
		removeCursor();
		menu(menuOption);
		if (_kbhit()) {
			switch (_getch()){
			case '0':
				system("cls");
				menuOption = 0;
				break;
			case '1':
				if (menuOption == 0) {
					system("cls");
					gameplay();
				}
				break;
			case '2':
				if (menuOption == 0) {
					system("cls");
					menuOption = 2;
				}
				break;
			case '3':
				if (menuOption == 0) {
					system("cls");
					menuOption = 3;
				}
				break;
			case '4':
				if (menuOption == 0) {
					system("cls");
					menuOption = 4;
				}
				break;
			case '5':
				if (menuOption == 0) {
					system("cls");
					menuShow = !menuShow;
				}
				break;
			case 'r':
				if (menuOption == 2)
					clearScoreboard();
			}
		}
		clear();
	}
	saveScoreboard();
}