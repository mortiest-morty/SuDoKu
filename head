#pragma once
#ifndef LUL_H
#define LUL_H
#include <iostream>
#include <stdlib.h>     
#include <cstring>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

void setColor(int bg, int fg = 15);
void resetColor();
void printScreensaver();

bool checkMenuCin(int choice);
bool checkLevelCin(int choice);
bool canPlace(int(&a)[9][9], int n, int m, int num);
int checkChange();
int checkPaste();
bool opportunityToPaste(int num, int x, int y, int(&a)[9][9]);

void fillDiagonal(int(&a)[9][9]);
bool fillEmpty(int(&a)[9][9], int  n, int m);
void playingField(int(&a)[9][9], int n, int m, int difficulty);
void printField(int(&a)[9][9], string begin);
void solveSudoku(int(&a)[9][9]);
bool checkMatrix(int(&a)[9][9]);
bool isFieldOk(int(&a)[9][9]);

int pasteNumber(int(&a)[9][9], string begin);
bool printMenu(int(&a)[9][9], string begin);
void newGame(int(&a)[9][9], string begin);
void continueGame(int(&a)[9][9],string begin);
bool loadGame(int(&a)[9][9]);
void gameLoop(int(&a)[9][9], string begin);

bool checkFile();
void saving(int(&a)[9][9]);

#endif
