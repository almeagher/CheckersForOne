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

Checkerboard:: Checkerboard(int  b[8][8]){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			prevBoard[i][j] = b[i][j];
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

void Checkerboard:: printLED(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			//cout << "(" << ledBoard[r][c].r << "," << ledBoard[r][c].g << "," << ledBoard[r][c].b << ") ";
		}
		//cout << endl;
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

coord Checkerboard:: getFromPiece(){
	return fromPiece;
}

void Checkerboard:: setFromPiece(int r, int c){
	fromPiece.x = r; 
	fromPiece.y = c; 
	//fromPiece = {r, c};
}

bool Checkerboard:: checkMoved(Driver &driver, vector<int> p){
	driver.scan();
	getNewBoard(driver.table);
	
	coord movedFrom {-2, -2};
	coord movedTo {-2, -2};
	int diffArray[8][8];
	bool alreadyMoved = false;
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			ledBoard[i][j].r = 0;
			ledBoard[i][j].g = 0;
			ledBoard[i][j].b = 0;
		}
	}
	driver.writeToLeds(ledBoard);

	/*
	cout << "Current board" << endl;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			cout << currBoard[r][c] << " ";
		}
		cout << endl;
	}
	
	cout << "PrevBoard board" << endl;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			cout << prevBoard[r][c] << " ";
		}
		cout << endl;
	}*/
	
	cout << endl;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if(currBoard[r][c] - prevBoard[r][c] == 1){
				movedFrom = {r, c};
				cout << movedFrom.x << movedFrom.y << endl;
			}
			/*else if(currBoard[r][c] - prevBoard[r][c] == 1 && alreadyMoved == true){
				cout << "you moved two different pieces at once" << endl;
				cout << movedFrom.x << movedFrom.y << movedTo.x << movedTo.y << endl;
				ledBoard[movedFrom.x][movedFrom.y] = redLed;
				ledBoard[r][c] = redLed;
			}*/
			else if(currBoard[r][c] - prevBoard[r][c] == -1){
				movedTo = {r, c};
				//alreadyMoved = true;
			}
		}
	}
	
	if(movedFrom.x == -2 && movedFrom.y == -2 && movedTo.x == -2 && movedTo.y == -2){
		//cout << "put piece down in same spot" << endl;
		return false;
	}
	
	else if(movedTo.x == -2 && movedTo.y == -2){
		cout << "transition mode" << endl;
		bool validMove = false;
		for(int i = 0; i < p.size()-2; i+= 4){
			if(p[i] == movedFrom.x && p[i+1] == movedFrom.y){
				ledBoard[p[i]][p[i+1]].r = 0;
				ledBoard[p[i]][p[i+1]].g = 0;
				ledBoard[p[i]][p[i+1]].b = 128;
				ledBoard[p[i+2]][p[i+3]].r = 0;
				ledBoard[p[i+2]][p[i+3]].g = 128;
				ledBoard[p[i+2]][p[i+3]].b = 0;
				validMove = true;
			}
		}
		if(validMove == false){
			ledBoard[movedFrom.x][movedFrom.y].r = 128;
			ledBoard[movedFrom.x][movedFrom.y].g = 0;
			ledBoard[movedFrom.x][movedFrom.y].b = 0;
			driver.writeToLeds(ledBoard);	
		}
		
		driver.writeToLeds(ledBoard);
		return false;		
	}
	/*else if(alreadyMoved == true){
		cout << "error state" << endl;
	}*/
	else{
		cout << movedFrom.x << " " << movedFrom.y << " -> " << movedTo.x << " " << movedTo.y << endl;
		pieceMoved = to_string(movedFrom.x) + " " + to_string(movedFrom.y) + " " + to_string(movedTo.x) + " " + to_string(movedTo.y) + " -1";
		bool validMove = false;
		for(int i = 0; i < p.size()-2; i+= 4){
			if(p[i+2] == movedTo.x && p[i+3] == movedTo.y){
				validMove = true;
				return true;
			}
		}
		if(validMove == false){
			ledBoard[movedFrom.x][movedFrom.y].r = 0;
			ledBoard[movedFrom.x][movedFrom.y].g = 0;
			ledBoard[movedFrom.x][movedFrom.y].b = 128;
			ledBoard[movedTo.x][movedTo.y].r = 128;
			ledBoard[movedTo.x][movedTo.y].g = 0;
			ledBoard[movedTo.x][movedTo.y].b = 0;
			driver.writeToLeds(ledBoard);	
			return false;
		}
		
		return false;
		// checkValidMove();
	}
	//return false;
}

void Checkerboard:: changeBoard(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			prevBoard[r][c] = currBoard[r][c];
		}
	}
}

string Checkerboard:: getPieceMoved(){
	string p = pieceMoved;
	pieceMoved = "";
	return p;
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
