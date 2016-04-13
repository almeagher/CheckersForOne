
#include <cstdlib>
#include <vector>
#include "Checkerboard.h"

using namespace std;

Checkerboard::Checkerboard(){
	char yellow = 'y';
	char black = 'r';
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if((r+c)%2 != 0 && r <=2)
				prevBoard[r][c] = yellow;
			else if((r+c)%2 != 0 && r > 1 && r <= 4)
				prevBoard[r][c] = 0;
			else if((r+c)%2 != 0 && r > 4 && r <= 7)
            prevBoard[r][c]=red;
			else
				prevBoard[r][c] = 0;
		}
	}
}

void Checkerboard:: printBoard(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			cout << board [r][c] << " ";
		}
		cout << endl;
	}
}

// void Checkerboard:: setPieces(){
	// char white = 'W';
	// char black = 'B';
	// for(int r = 0; r < 8; r++){
		// for(int c = 0; c < 8; c++){
			// if((r+c)%2 != 0 && r <=2)
				// board[r][c] = white;
			// else if((r+c)%2 != 0 && r > 1 && r <= 4)
				// board[r][c] = 0;
			// else if((r+c)%2 != 0 && r > 4 && r <= 7)
            // board[r][c]=black;
			// else
				// board[r][c] = board[r][c];
		// }
	// }
// }

void Checkerboard:: getNewBoard(vector<vector<bool>> newBoard){
	vector <vector <int>> board2 (8, vector<int>(8));
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(newBoard[i][j] == 1 && board[i][j] == 0){
				if(board[i-1][j-1] == 'Y' || board[i-1][j-1] == 'R'){
					board[i][j] = board[i-1][j-1];
					board[i-1][j-1] = 0;
				}
				else if(board[i-1][j-1] == 'Y' || board[i-1][j+1] == 'R'){
					board[i][j] = board[i-1][j+1];
					board[i-1][j-1] = 0;
				}
				else
					cout << "invalid move";
			}
				
			
		}
	}
}

bool Checkerboard:: checkValidMove(){
	if(checkMovedLeft() || checkMovedRight() || checkJumped())
		return true;
	return false;
}

bool Checkerboard:: checkMovedLeft(){
	return false;
}

bool Checkerboard:: checkMovedRight(){
	return false;
}

bool Checkerboard:: checkJumped(){
	
	return false;
}

void Checkerboard:: checkState(){
	
}

void Checkerboard:: moveState(){
	
}

void Checkerboard:: transitionState(){
	
}

void Checkerboard:: errorState(){
	
}

// Checkerboard::~Checkerboard(){
	// for(int r = 0; r < 8; r++){
		// for(int c = 0; c < 8; c++){
			// delete board[r][c];
		// }
		// delete[] board[r];
	// }
	// delete[] board;
// }