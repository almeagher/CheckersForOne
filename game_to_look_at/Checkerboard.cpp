#include <iostream>
#include <vector>
#include "Checkerboard.h"

using namespace std;

Checkerboard::Checkerboard(){
	
	char black = 'b';
	char red = 'r';
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			board [r][c] = 0;
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
				// prevBoard[r][c]=red;
				prevBoard[r][c]= 1;
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

void Checkerboard:: getNewBoard(int newBoard[8][8]){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			board[r][c] = newBoard[r][c];
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			cout << board[r][c] << " ";
		}
		cout << endl;
	}
	
}

char Checkerboard:: getPieceType(int prevCoorR, int prevCoorC){
	return prevBoard[prevCoorR][prevCoorC];
}


void Checkerboard:: showPossibleMoves(int r, int c){
	
}

bool Checkerboard:: checkThinking(int r, int c){
	if(board[r][c] == 0 && !checkMovedLeft(r, c) && !checkMovedRight(r, c)){
		return true;
	}
	return false;
}

bool Checkerboard:: checkMovedLeft(int r, int c){
	
	// if top player
	if(board[r][c] == prevBoard[r-1][c+1] && board[r-1][c+1] == 0){
		// newPieceType = getPieceType((r-1), (c+1));
		cout << "Moved " << r-1 << " " << c+1 << " to " << r << " " << c << endl;
		return true;
	}
		
	// if bottom player
	else if(board[r][c] == prevBoard[r+1][c+1] && board[r+1][c+1] == 0){
		// newPieceType = getPieceType((r+1), (c+1));
		return true;
	}
		
	else
		return false;
	
	return false;
}

bool Checkerboard:: checkMovedRight(int r, int c){
	// if top player
	if(board[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
		// newPieceType = getPieceType((r-1), (c-1));
		return true;
	}
		
	// if bottom player
	else if(board[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
		// newPieceType = getPieceType((r+1), (c-1));
		return true;
	}
		
	else
		return false;
	return false;
}


void Checkerboard:: checkMoved(){
	// cout << "PREV BOARD: " << endl;
	// for(int r = 0; r < 8; r++){
		// for(int c = 0; c < 8; c++){
			// cout << prevBoard[r][c] << " ";
		// }
		// cout << endl;
	// }
	// cout << "NEW BOARD: " << endl;
	// for(int r = 0; r < 8; r++){
		// for(int c = 0; c < 8; c++){
			// cout << board[r][c] << " ";
		// }
		// cout << endl;
	// }
	
	
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			//LEFT
			if(board[r][c] == prevBoard[r-1][c-1] && board[r-1][c-1] == 0){
				// cout << "Moved " << r-1 << " " << c+1 << " to " << r << " " << c << endl;
				// cout << "Moved left" << endl;
			}
			else if(board[r][c] == prevBoard[r+1][c+1] && board[r+1][c+1] == 0){
				// cout << "Moved left" << endl;
			} //RIGHT
			else if(board[r][c] == prevBoard[r-1][c+1] && board[r-1][c+1] == 0){
				// cout << "Moved right" << endl;
			}
			else if(board[r][c] == prevBoard[r+1][c-1] && board[r+1][c-1] == 0){
				// cout << "Moved right" << endl;
			}
			else {
				
				
			}
			// else if(){ // piece is picked up
				
			// }
			// else if(){ // piece jumped
				
			// }
			
			// if(checkMovedLeft(r, c) || checkMovedRight(r, c)){
				// checkValidMove(newPieceType, r, c);
			// }
			// else if(checkJumped(r, c)){
				// checkValidMove(newPieceType, r, c);
			// }
			// else if(checkThinking(r, c)){
				// showPossibleMoves(r, c);
			// }
			// else{
				
			// }
		}
	}
}

bool Checkerboard:: checkValidMove(char oldPieceType, int r, int c){
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