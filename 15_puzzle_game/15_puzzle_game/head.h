#pragma once

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<fstream>
#include<random>
#include<windows.h>
#include<string>

using namespace std;

void clear();
void removeCursor();
void menu(int number);
void fontSize();
void fullScreen();

void showRules();
void showAuthor();

void loadScoreboard();
void saveScoreboard();
void showScoreboard();
void addToScoreboard(string name, int score);
void clearScoreboard();

void makeBoard(int b[4][4]);
void showBoard(int b[4][4], int ePoss[2]);

void moveCell(int b[4][4], int ePoss[2], int dir);
void switchNumbers(int b[4][4], int ePossPrev[2], int ePoss[2]);

void shuffle(int b[4][4], int ePoss[2], int iteration);

bool winCheck(int b[4][4]);
void showScore(int score);