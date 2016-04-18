
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
	// vector <vector <int>> board2 (8, vector<int>(8));
	board.insert(board.end(), newBoard.begin(), newBoard.end());
	// for(int i = 0; i < 8; i++){
		// for(int j = 0; j < 8; j++){
			// if(newBoard[i][j] == 1 && board[i][j] == 0){
				// if(board[i-1][j-1] == 'Y' || board[i-1][j-1] == 'R'){
					// board[i][j] = board[i-1][j-1];
					// board[i-1][j-1] = 0;
				// }
				// else if(board[i-1][j-1] == 'Y' || board[i-1][j+1] == 'R'){
					// board[i][j] = board[i-1][j+1];
					// board[i-1][j-1] = 0;
				// }
				// else
					// cout << "invalid move";
			// }
				
			
		// }
	// }
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			
		}
	}
}

char getPieceType(int prevCoorR, int prevCoorC){
	return prevBoard[prevCoorR][prevCoorC];
}

void Checkerboard:: checkMoved(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if(checkMovedLeft(r, c) || checkMovedRight(r, c)){
				checkValidMove(newPieceType, r, c);
			}
			else if(checkJumped(r, c)){
				checkValidMove(newPieceType, r, c);
			}
			else if(checkThinking(r, c)){
				showPossibleMoves(r, c);
			}
			else{
				
			}
		}
	}
}

bool Checkerboard:: checkThinking(int r, int c){
	if(board[i][j] == 0 && !checkMovedLeft() && !checkMovedRight()){
		return true;
	}
	return false;
}

bool Checkerboard:: checkMovedLeft(){
	
	// if top player
	if(board[r][c] == prevBoard[r-1][c+1] && board[r-1][c+1] == 0){
		newPieceType = getPieceType((r-1), (c+1));
		return true;
	}
		
	// if bottom player
	else if(board[r][c] == prevBoard[r+1][c+1] && board[r+1][c+1] == 0){
		newPieceType = getPieceType((r+1), (c+1));
		return true;
	}
		
	else
		return false;
	
	return false;
}

bool Checkerboard:: checkMovedRight(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			// if top player
			if(board[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
				newPieceType = getPieceType((r-1), (c-1));
				return true;
			}
				
			// if bottom player
			else if(board[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
				newPieceType = getPieceType((r+1), (c-1));
				return true;
			}
				
			else
				continue;
		}
	}
	return false;
}

bool Checkerboard:: checkValidMove(r, c){
	if(board[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
		newPieceType = getPieceType((r-1), (c-1));
		return true;
	}
		
	// if bottom player
	else if(board[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
		newPieceType = getPieceType((r+1), (c-1));
		return true;
	}
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