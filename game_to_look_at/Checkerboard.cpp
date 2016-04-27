#include <iostream>
#include <vector>
#include "Checkerboard.h"

using namespace std;

Checkerboard::Checkerboard(){
	
	char black = 'b';
	char red = 'r';
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			board [r][c] = '0';
		}
	}
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			ledBoard [r][c] = blank;
		}
	}
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if((r+c)%2 != 0 && r <=2)
				// prevBoard[r][c] = black;
				prevBoard[r][c] = '1';
			else if((r+c)%2 != 0 && r > 1 && r <= 4)
				prevBoard[r][c] = '0';
			else if((r+c)%2 != 0 && r > 4 && r <= 7)
				// prevBoard[r][c]=red;
				prevBoard[r][c]= '1';
			else
				prevBoard[r][c] = '0';
		}
	}
}

void Checkerboard:: printBoard(){
	cout << "    0 1 2 3 4 5 6 7" << endl;
	cout << "-------------------" << endl;
	for(int r = 0; r < 8; r++){
		cout << r << " | ";
		for(int c = 0; c < 8; c++){
			cout << board [r][c] << " ";
		}
		cout << endl;
	}
}

void Checkerboard:: setPlayers(bool p1, bool p2){
	checkers.playTheGame(p1, p2);
	// 
	
}

void Checkerboard:: printLED(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			cout << "(" << ledBoard[r][c].r << "," << ledBoard[r][c].g << "," << ledBoard[r][c].b << ") ";
		}
		cout << endl;
	}
}

void Checkerboard:: getNewBoard(char newBoard[8][8]){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			board[r][c] = newBoard[r][c];
		}
	}
}

// char Checkerboard:: getPieceType(int prevCoorR, int prevCoorC){
	// return prevBoard[prevCoorR][prevCoorC];
// }

void Checkerboard:: showPossibleMoves(int r, int c){
	
}

bool Checkerboard:: checkThinking(int r, int c){
	// if(board[r][c] == 0 && !checkMovedLeft(r, c) && !checkMovedRight(r, c)){
		// return true;
	// }
	return false;
}

// bool Checkerboard:: checkMovedLeft(int r, int c){
	// // if top player
	// if(board[r][c] == prevBoard[r-1][c+1] && board[r-1][c+1] == 0){
		// // newPieceType = getPieceType((r-1), (c+1));
		// cout << "Moved " << r-1 << " " << c+1 << " to " << r << " " << c << endl;
		// return true;
	// }
		
	// // if bottom player
	// else if(board[r][c] == prevBoard[r+1][c+1] && board[r+1][c+1] == 0){
		// // newPieceType = getPieceType((r+1), (c+1));
		// return true;
	// }
		
	// else
		// return false;
	
	// return false;
// }

// bool Checkerboard:: checkMovedRight(int r, int c){
	// // if top player
	// if(board[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
		// // newPieceType = getPieceType((r-1), (c-1));
		// return true;
	// }
		
	// // if bottom player
	// else if(board[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
		// // newPieceType = getPieceType((r+1), (c-1));
		// return true;
	// }
		
	// else
		// return false;
	// return false;
// }


void Checkerboard:: checkMoved(){
	coord movedFrom {-2, -2};
	coord movedTo {-2, -2};
	cout << "Diff array" << endl;
	int diffArray[8][8];
	bool pieceMoved = false;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			diffArray[r][c] = board[r][c] - prevBoard[r][c];
			cout << diffArray[r][c] << " ";
			if(board[r][c] - prevBoard[r][c] == -1 && pieceMoved == false){
				movedFrom = {r, c};
				pieceMoved = true;
			}
			else if(board[r][c] - prevBoard[r][c] == -1 && pieceMoved == true){
				cout << "you moved two different pieces at once" << endl;
				ledBoard[movedFrom.x][movedFrom.y] = error;
				ledBoard[r][c] = error;
			}
			if(board[r][c] - prevBoard[r][c] == 1 && pieceMoved == false){
				movedTo = {r, c};
			}
		}
		cout << endl;
	}
	
	if(movedFrom.x == -2 && movedFrom.y == -2 && movedTo.x == -2 && movedTo.y == -2){
		cout << "didn't move" << endl;
	}
	
	else if(movedTo.x == -2 && movedTo.y == -2){
		cout << "transition mode" << endl;
		showPossibleMoves(movedFrom.x, movedFrom.y);
	}
	else if(pieceMoved == true){
		cout << "error state" << endl;
	}
	else{
		cout << movedFrom.x << " " << movedFrom.y << " -> " << movedTo.x << " " << movedTo.y << endl;
		// checkValidMove();
	}
}

// bool Checkerboard:: checkValidMove(char oldPieceType, int r, int c){
	// if(board[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
		// newPieceType = getPieceType((r-1), (c-1));
		// return true;
	// }
		
	// // if bottom player
	// else if(board[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
		// newPieceType = getPieceType((r+1), (c-1));
		// return true;
	// }
// }

bool Checkerboard:: checkJumped(int r, int c){
	
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