/****************************************************************
*
* File: Assignment01 — TicTacToe
* By: Sam Zaffanella
* Date: 6/15/2018
*
* Description: A simple array program that plays a tic-tac-toe game
*              
*
****************************************************************/
#include <iostream>
#include <string>
using namespace std;

//This class is used to determine if the current player is the winner (Either X or O)
bool isWon(char place, char board[][3]) {
	bool hor = true;
	bool vert = true;
	//These boolean variables are later used to determine if a player won (Horizontally or diagonally)
	for (int i = 0; i < sizeof(board) - 1; i++) {
		for (int j = 0; j < sizeof(board) - 1; j++) {
			//Nested for loops to be able to check each location within the array
			if (board[i][j] != place) {
				hor = false;
			}
			if (board[j][i] != place) {
				vert = false;
			}
		}
		if (vert == true || hor == true) {
			return true;
		}
		//if either bool variable stays true, then the bool class will return true
		hor = true;
		vert = true;
		//reset to true in order to go through the for loop again
	}
	if (board[1][1] == place) {
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			return true;
		}
		else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
			return true;
		}
	}
	//used to check if player X/O has a diagonal win
	return false;
}
bool isDraw(char board[][3]) {
	//checks if game ends in a draw by checking if any of the quadrants are empty or ' '
	for (int i = 0; i < sizeof(board) - 1; i++) {
		for (int j = 0; j < sizeof(board) - 1; j++) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}
void displayBoard(char x[][3]) {
	//displays board through simple if statement
	cout << "--------------" << endl;
	for (int i = 0; i < sizeof(x) - 1; i++) {
		for (int j = 0; j < sizeof(x[i]); j++) {
			cout << "| " << x[i][j] << " ";
		}
		cout << "|" << endl;
		cout << "--------------" << endl;
	}
}
void makeAMove(char board[][3], char move) {
	//used to let player choose where they want to make their move through 2 inputs
	cout << "Enter a row (0, 1, 2) for player " << move << ": ";
	int row;
	cin >> row;
	cout << "Enter a collumn (0, 1, 2) for player " << move << ": ";
	int col;
	cin >> col;
	if (board[row][col] == ' ') {
		board[row][col] = move;
		cout << endl;
	}
	else {
		cout << "This cell is already occupied. Try a different cell." << endl;
		makeAMove(board, move);
	}
}

int main() {
	//
	//	PLEASE DO NOT CHANGE main()
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);
	while (true) {
		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);
		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
}