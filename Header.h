#ifndef __HEADER_H__
#define __HEADER_H__

enum INPUT_RESULT;

void displayBoard(int[], int);
void initializeBoard(int[], int);
INPUT_RESULT inputMove(int[], int, const int&);
bool checkForWin(int[], int);
char convertToOutput(int);

#endif