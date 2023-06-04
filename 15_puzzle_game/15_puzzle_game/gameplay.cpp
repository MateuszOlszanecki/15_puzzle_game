#include"head.h"

void clear() {
	COORD c = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void fullScreen() {
	::SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void removeCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void fontSize() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 50;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void makeBoard(int b[4][4]) {
	int n = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			b[i][j] = n;
			n++;
		}
	}
}

void showBoard(int b[4][4], int ePoss[2]) {
	cout << (char)201 << setfill((char)205) << setw(5) << (char)203 << setw(5) << (char)203 << setw(5) << (char)203 << setw(5) << (char)187 << endl;
	for (int i = 0; i < 4; i++) {
		cout << (char)186;
		for (int j = 0; j < 4; j++) {
			if(i == ePoss[0] && j == ePoss[1])
				cout << setfill(' ') << setw(3) << " " << " " << (char)186;
			else
				cout << setfill(' ') << setw(3) << b[i][j] << " " << (char)186;
		}
		cout << endl;
		if (i != 3)
			cout << (char)204 << setfill((char)205) << setw(5) << (char)206 << setw(5) << (char)206 << setw(5) << (char)206 << setw(5) << (char)185 << endl;
	}
	cout << (char)200 << setfill((char)205) << setw(5) << (char)202 << setw(5) << (char)202 << setw(5) << (char)202 << setw(5) << (char)188 << endl;
}

void moveCell(int b[4][4], int ePoss[2], int dir) {
	int ePossPrev[2];
	ePossPrev[0] = ePoss[0];
	ePossPrev[1] = ePoss[1];
	switch (dir) {
	case 0:
		ePoss[0]++;
		switchNumbers(b, ePossPrev, ePoss);
		break;
	case 1:
		ePoss[1]++;
		switchNumbers(b, ePossPrev, ePoss);
		break;
	case 2:
		ePoss[0]--;
		switchNumbers(b, ePossPrev, ePoss);
		break;
	case 3:
		ePoss[1]--;
		switchNumbers(b, ePossPrev, ePoss);
		break;
	}
}

void switchNumbers(int b[4][4], int ePossPrev[2], int ePoss[2]) {
	int tmp = b[ePossPrev[0]][ePossPrev[1]];
	b[ePossPrev[0]][ePossPrev[1]] = b[ePoss[0]][ePoss[1]];
	b[ePoss[0]][ePoss[1]] = tmp;
}

void shuffle(int b[4][4], int ePoss[2], int iteration) {
	int i = 0;
	int prevDir = -1;
	random_device rnd;
	mt19937 generator(rnd());
	uniform_int_distribution <int> distribution(0,3);
	int dir;
	while (i < iteration) {
		dir = distribution(rnd);
		if (dir != prevDir && dir != (prevDir + 2) % 4) {
			if (dir == 0 && ePoss[0] < 3) {
				moveCell(b, ePoss, dir);
				prevDir = dir;
				i++;
			}
			else if (dir == 1 && ePoss[1] < 3) {
				moveCell(b, ePoss, dir);
				prevDir = dir;
				i++;
			}
			else if (dir == 2 && ePoss[0] > 0) {
				moveCell(b, ePoss, dir);
				prevDir = dir;
				i++;
			}
			else if (dir == 3 && ePoss[1] > 0) {
				moveCell(b, ePoss, dir);
				prevDir = dir;
				i++;
			}
		}
	}
}

bool winCheck(int b[4][4]) {
	bool start = true;
	int n = 1;
	int isGood = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b[i][j] == n)
				isGood++;
			n++;
		}
	}
	if (isGood == 16) {
		cout << endl;
		cout << "You solved it!                       " << endl;
		cout << "Type your name: ";
		return false;
	}
	return true;
}

void showScore(int score) {
	cout << "Number of moves: " << score << endl;
}

void menu(int number) {
	switch (number) {
	case 0:
		cout << "15 puzzle game" << endl << endl;
		cout << "1. Play" << endl;
		cout << "2. Scoreboard" << endl;
		cout << "3. Rules of the game" << endl;
		cout << "4. Author" << endl;
		cout << "5. Quit" << endl;
		break;
	case 2:
		showScoreboard();
		break;
	case 3:
		showRules();
		break;
	case 4:
		showAuthor();
		break;
	}
}

void showAuthor() {
	cout << "AUTHOR: " << endl << endl;
	cout << "Mateusz Olszanecki" << endl;
	cout << "Informatics, term I" << endl;
	cout << "group 3F" << endl << endl;
	cout << "Press '0' to quit author info" << endl;
}

void showRules() {
	int n = 1;
	cout << "You move tails by pressing:" << endl;
	cout << "'w' -> UP  'a' -> LEFT  's' -> DOWN  'd' -> RIGHT" << endl;
	cout << "The goal is to rearrange tails to get solved state" << endl << "that looks like this one:" << endl;
	cout << (char)201 << setfill((char)205) << setw(5) << (char)203 << setw(5) << (char)203 << setw(5) << (char)203 << setw(5) << (char)187 << endl;
	for (int i = 0; i < 4; i++) {
		cout << (char)186;
		for (int j = 0; j < 4; j++) {
			if (n != 16)
				cout << setfill(' ') << setw(3) << n << " " << (char)186;
			else
				cout << setfill(' ') << setw(4) << " " << (char)186;
			n++;
		}
		cout << endl;
		if (i != 3)
			cout << (char)204 << setfill((char)205) << setw(5) << (char)206 << setw(5) << (char)206 << setw(5) << (char)206 << setw(5) << (char)185 << endl;
	}
	cout << (char)200 << setfill((char)205) << setw(5) << (char)202 << setw(5) << (char)202 << setw(5) << (char)202 << setw(5) << (char)188 << endl;
	cout << "Press '0' to quit rules" << endl;
}

string bestNames[10];
int bestNumbers[10];

void loadScoreboard() {
	clearScoreboard();
	fstream file("scoreboard.txt", ios::in);
	if (file.is_open()) {
		for (int i = 0; i < 10; i++) {
			file >> bestNames[i];
			file >> bestNumbers[i];
		}
	}
}

void showScoreboard() {
	cout << setfill(' ');
	cout << " Place      Name              Moves" << endl;
	for (int i = 0; i < 10; i++) {
		cout << right << "  " << setw(2) << (i + 1) << ".       " << left << setw(20) << bestNames[i] << left << setw(6) << bestNumbers[i] << endl;
	}
	cout << right;
	cout << endl;
	cout << "   Press 'r' to reset scoreboard" << endl;
	cout << "   Press '0' to quit scoreboard" << endl;
}

void addToScoreboard(string name, int score) {
	for (int i = 0; i < 10; i++) {
		if (bestNumbers[i] == 0) {
			bestNumbers[i] = score;
			bestNames[i] = name;
			break;
		}
		else if (score < bestNumbers[i]){
			for (int j = 8; j >= i; j--) {
				bestNumbers[j + 1] = bestNumbers[j];
				bestNames[j + 1] = bestNames[j];
			}
			bestNumbers[i] = score;
			bestNames[i] = name;
			break;
		}
	}
}

void saveScoreboard() {
	fstream file("scoreboard.txt", ios::out);
	if (file.is_open()) {
		for (int i = 0; i < 10; i++) {
			file << bestNames[i] << " " << bestNumbers[i] << endl;
		}
	}
}

void clearScoreboard() {
	for (int i = 0; i < 10; i++) {
		bestNames[i] = { "----------" };
		bestNumbers[i] = 0;
	}
}