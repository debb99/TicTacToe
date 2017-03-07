#include <iostream>
#include <iomanip>
#include "Header.h"

#define BOARD_WIDTH 3
#define PLAYER_X 1
#define PLAYER_O -1

enum INPUT_RESULT {
	OUT_OF_BOUNDS, SPOT_TAKEN, NOT_A_NUMBER, SUCCESS
};

using namespace std;

int main() {
	const int size = BOARD_WIDTH * BOARD_WIDTH;
	int boardSpaces[size];
	initializeBoard(boardSpaces, size);

	bool gameComplete = false;
	int currentPlayer = PLAYER_X;

	/*
	Current issues:
	max/min values for user input
	non-number values
	selecting elements that are already taken
	*/
	while (!gameComplete) {
		//display the current board
		displayBoard(boardSpaces, size);

		//prompt the player to input a coordinate
		INPUT_RESULT moveResult = SUCCESS;
		do {
			moveResult = inputMove(boardSpaces, size, currentPlayer);

			switch (moveResult)
			{
			case OUT_OF_BOUNDS:
				cout << "That spot does not exist within the board. Please try again." << endl;
				break;
			case SPOT_TAKEN:
				cout << "That spot is already taken. Please try again." << endl;
				break;
			case NOT_A_NUMBER:
				cout << "Please input a valid number." << endl;
				break;
			default:
				break;
			}
		} while (moveResult != SUCCESS);

		if (checkForWin(boardSpaces, size)) {
			gameComplete = true;
			cout << endl;
			displayBoard(boardSpaces, size);
			cout << endl << "The winner is player " << convertToOutput(currentPlayer) << "!" << endl;
		}
		
		currentPlayer *= -1;

		cout << endl;
	}
	char c;
	cin >> c;

	return 0;
}

void displayBoard(int board[], int size) {
	//output board with ROW x COLUMN format

	int padding = 2;

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			cout << setw(padding) << setfill(' ') << convertToOutput(board[i * BOARD_WIDTH + j]);
			if (j != BOARD_WIDTH - 1) {
				cout << setw(padding) << setfill(' ') << '|';
			}
		}
		if (i != BOARD_WIDTH - 1) {
			cout << endl << setw(2 * padding * BOARD_WIDTH) << setfill('-') << '\n';
		}
		else {
			cout << '\n' << '\n';
		}
	}
}

void initializeBoard(int board[], int size) {
	//initialize board with all 0
	for (int i = 0; i < size; i++) {
		board[i] = 0;
	}
}

INPUT_RESULT inputMove(int board[], int size, const int &player) {
	INPUT_RESULT moveResult = SUCCESS;
	cout << "Current player: " << convertToOutput(player) << endl;

	cout << "Input: ";
	int row = 0;
	int col = 0;
	cin >> row >> col;

	if (cin.fail()) {
		moveResult = NOT_A_NUMBER;
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');
		return moveResult; //is there a better way to organize this?
	}

	int index = (row - 1) * BOARD_WIDTH + col - 1; //convert row/col input into the array index

	if (index > size - 1 || index < 0) {
		moveResult = OUT_OF_BOUNDS;
	} else if (board[index] != 0) {
		moveResult = SPOT_TAKEN;
	} 

	if (moveResult == SUCCESS) board[index] = player;

	return moveResult;
}

bool checkForWin(int board[], int size) {
	int leftDiagSum = 0;
	int rightDiagSum = 0;

	for (int i = 0; i < BOARD_WIDTH; i++) {
		//check rows
		int rowSum = 0;
		for (int j = 0; j < BOARD_WIDTH; j++) {
			rowSum += board[i * BOARD_WIDTH + j];
		}

		//check columns
		int colSum = 0;
		for (int j = 0; j < BOARD_WIDTH; j++) {
			colSum += board[j * BOARD_WIDTH + i];
		}

		//check diagonals
		leftDiagSum += board[i * BOARD_WIDTH + i];
		rightDiagSum += board[(BOARD_WIDTH - 1) * (i + 1)];

		//if the sum adds up the the width of the board, they won
		if (abs(rowSum) == BOARD_WIDTH || abs(colSum) == BOARD_WIDTH) {
			return true;
		}
	}
	if (abs(leftDiagSum) == BOARD_WIDTH || abs(rightDiagSum) == BOARD_WIDTH) {
		return true;
	}

	return false;
}

char convertToOutput(int original) {
	char result = ' ';

	switch (original)
	{
	case PLAYER_O: result = 'O';
		break;
	case PLAYER_X: result = 'X';
		break;
	default:
		break;
	}

	return result;
}