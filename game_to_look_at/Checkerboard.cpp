#include <iostream>
#include <vector>
#include "Checkerboard.h"
#include "board.h"

using namespace std;

Checkerboard::Checkerboard(){
	
	char black = 'b';
	char redPiece = 'r';
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			currBoard [r][c] = 0;
		}
	}
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			//ledBoard [r][c] = blank;
		}
	}
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if((r+c)%2 != 0 && r <=2)
				// prevBoard[r][c] = black;
				prevBoard[r][c] = 1;
			else if((r+c)%2 != 0 && r > 1 && r <= 4)
				prevBoard[r][c] = 0;
			else if((r+c)%2 != 0 && r > 4 && r <= 7)
				// prevBoard[r][c]=redPiece;
				prevBoard[r][c]= 1;
			else
				prevBoard[r][c] = 0;
		}
	}
}

void Checkerboard:: printBoard(){
	cout << "    0 1 2 3 4 5 6 7" << endl;
	cout << "-------------------" << endl;
	for(int r = 0; r < 8; r++){
		cout << r << " | ";
		for(int c = 0; c < 8; c++){
			cout << currBoard [r][c] << " ";
		}
		cout << endl;
	}
}

// void Checkerboard:: setPlayers(bool p1, bool p2, Driver &driver){
	// checkers.playTheGame(p1, p2,driver);
	// // 
	
// }

void Checkerboard:: printLED(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			//cout << "(" << ledBoard[r][c].r << "," << ledBoard[r][c].g << "," << ledBoard[r][c].b << ") ";
		}
		cout << endl;
	}
}

void Checkerboard:: getNewBoard(int newBoard[8][8]){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			currBoard[r][c] = newBoard[r][c];
		}
	}
}

void Checkerboard:: showPossibleMoves(int r, int c){
	
}

bool Checkerboard:: checkThinking(int r, int c){
	// if(board[r][c] == 0 && !checkMovedLeft(r, c) && !checkMovedRight(r, c)){
		// return true;
	// }
	return false;
}

void Checkerboard:: checkMoved(){
	coord movedFrom {-2, -2};
	coord movedTo {-2, -2};
	int diffArray[8][8];
	bool alreadyMoved = false;
	
	cout << "Diff array" << endl;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			diffArray[r][c] = currBoard[r][c] - prevBoard[r][c];
			cout << diffArray[r][c] << " ";
			if(currBoard[r][c] - prevBoard[r][c] == -1 && alreadyMoved == false){
				movedFrom = {r, c};
				alreadyMoved = true;
			}
			else if(currBoard[r][c] - prevBoard[r][c] == -1 && alreadyMoved == true){
				cout << "you moved two different pieces at once" << endl;
				//ledBoard[movedFrom.x][movedFrom.y] = redLed;
				//ledBoard[r][c] = redLed;
			}
			if(currBoard[r][c] - prevBoard[r][c] == 1 && alreadyMoved == false){
				movedTo = {r, c};
			}
		}
		cout << endl;
	}
	
	if(movedFrom.x == -2 && movedFrom.y == -2 && movedTo.x == -2 && movedTo.y == -2){
		cout << "put piece down in same spot" << endl;
	}
	
	else if(movedTo.x == -2 && movedTo.y == -2){
		cout << "transition mode" << endl;
		showPossibleMoves(movedFrom.x, movedFrom.y);
	}
	else if(alreadyMoved == true){
		cout << "error state" << endl;
	}
	else{
		cout << movedFrom.x << " " << movedFrom.y << " -> " << movedTo.x << " " << movedTo.y << endl;
		pieceMoved = to_string(movedFrom.x) + " " + to_string(movedFrom.y) + " " + to_string(movedTo.x) + " " + to_string(movedTo.y) + " -1";
		// checkValidMove();
	}
}

string Checkerboard:: getPieceMoved(){
	return pieceMoved;
}

// bool Checkerboard:: checkValidMove(char oldPieceType, int r, int c){
	// if(currBoard[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
		// newPieceType = getPieceType((r-1), (c-1));
		// return true;
	// }
		
	// // if bottom player
	// else if(currBoard[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
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
		// delete[] currBoard[r];
	// }
	// delete[] currBoard;
// }
