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

bool Checkerboard:: canStart(Driver &driver){
	int arr[8][8] = {
		{1,0,1,0,1,0,1,0},
		{0,1,0,1,0,1,0,1},
		{1,0,1,0,1,0,1,0},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{0,1,0,1,0,1,0,1},
		{1,0,1,0,1,0,1,0},
		{0,1,0,1,0,1,0,1}
	};
	driver.scan();
	getNewBoard(driver.table);
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if(currBoard[r][c] - arr[r][c] != 0){
				ledBoard[r][c].r = 128;
				ledBoard[r][c].g = 0;
				ledBoard[r][c].b = 0;
				return false;
			}
		}
	}
	return true;
	
}


void Checkerboard:: printCurrBoard(){
	cout << "Current Board::" << endl;
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

void Checkerboard:: printPrevBoard(){
	cout << "Previous Board::" << endl;
	cout << "    0 1 2 3 4 5 6 7" << endl;
	cout << "-------------------" << endl;
	for(int r = 0; r < 8; r++){
		cout << r << " | ";
		for(int c = 0; c < 8; c++){
			cout << prevBoard [r][c] << " ";
		}
		cout << endl;
	}
}

void Checkerboard:: printLedBoard(){
	cout << "Led Board::" << endl;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			cout << "(" << ledBoard[r][c].r << "," << ledBoard[r][c].g << "," << ledBoard[r][c].b << ") ";
		}
		cout << endl;
	}
}

void Checkerboard:: clearLedBoard(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			ledBoard[i][j].r = 0;
			ledBoard[i][j].g = 0;
			ledBoard[i][j].b = 0;
		}
	}
}


void Checkerboard:: changeBoard(){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			prevBoard[r][c] = currBoard[r][c];
		}
	}
}

void Checkerboard:: getNewBoard(int newBoard[8][8]){
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			currBoard[r][c] = newBoard[r][c];
		}
	}
}


string Checkerboard:: getPieceMoved(){
	string p = pieceMoved;
	pieceMoved = "";
	return p;
}

vector<vector<int>> Checkerboard:: createVector(coord moveF, coord moveT){
	vector<vector<int>> p;
	vector<int> x;
	x.push_back(moveF.x);
	x.push_back(moveF.y);
	x.push_back(moveT.x);
	x.push_back(moveT.y);
	p.push_back(x);
	return p;
}

void Checkerboard:: showPossibleMoves(Driver &driver, vector<vector<int>> p){
	for(int r = 0; r < p.size(); r++){
		if(p[r].size() > 4){
			for(int c = 0; c < p[r].size(); c+=2){
				ledBoard[p[r][c]][p[r][c+1]].r = 0;
				ledBoard[p[r][c]][p[r][c+1]].g = 0;
				ledBoard[p[r][c]][p[r][c+1]].b = 128;
				ledBoard[p[r][c+2]][p[r][c+3]].r = 0;
				ledBoard[p[r][c+2]][p[r][c+3]].g = 128;
				ledBoard[p[r][c+2]][p[r][c+3]].b = 0;
			}
		}
		else{
			ledBoard[p[r][0]][p[r][1]].r = 0;
			ledBoard[p[r][0]][p[r][1]].g = 0;
			ledBoard[p[r][0]][p[r][1]].b = 128;
			ledBoard[p[r][2]][p[r][3]].r = 0;
			ledBoard[p[r][2]][p[r][3]].g = 128;
			ledBoard[p[r][2]][p[r][3]].b = 0;
		}
	}
	//driver.writeToLeds(ledBoard);
}



bool Checkerboard:: waitUntilMoved(Driver &driver, coord moveF, coord moveT){
	driver.scan();
	getNewBoard(driver.table);
	int diffBoard[8][8];
	
	if(currBoard[moveF.x][moveF.y] - prevBoard[moveF.x][moveF.y] == 1 && currBoard[moveT.x][moveT.y] - prevBoard[moveT.x][moveT.y] == -1){
		changeBoard();
		//driver.clear_led();
		clearLedBoard();
		driver.writeToLeds(ledBoard);
		
		checkJumped(driver, createVector(moveF, moveT), moveF, moveT);
		return true;
	}
	
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
	ledBoard[moveF.x][moveF.y].r = 0;
	ledBoard[moveF.x][moveF.y].g = 0;
	ledBoard[moveF.x][moveF.y].b = 128;
	ledBoard[moveT.x][moveT.y].r = 0;
	ledBoard[moveT.x][moveT.y].g = 128;
	ledBoard[moveT.x][moveT.y].b = 0;
	driver.writeToLeds(ledBoard);
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if(currBoard[r][c] - prevBoard[r][c] == 1){
				movedFrom = {r, c};
			}
			else if(currBoard[r][c] - prevBoard[r][c] == -1){
				movedTo = {r, c};
			}
		}
	}
	
	if(movedFrom.x == -2 && movedFrom.y == -2 && movedTo.x == -2 && movedTo.y == -2){
	}
	else if(movedTo.x == -2 && movedTo.y == -2){
		cout << "transition mode AI" << endl;
		bool validMove = false;
		if(movedFrom.x == moveF.x && movedFrom.y == moveF.y){
			checkJumped(driver, createVector(moveF, moveT), moveF, moveT);
			validMove = true;
		}
		if(validMove == false){
			ledBoard[movedFrom.x][movedFrom.y].r = 128;
			ledBoard[movedFrom.x][movedFrom.y].g = 0;
			ledBoard[movedFrom.x][movedFrom.y].b = 0;
			driver.writeToLeds(ledBoard);	
		}
	}
	else{
		if(!(movedFrom.x == moveF.x && movedFrom.y == moveF.y)){
			ledBoard[movedFrom.x][movedFrom.y].r = 128;
			ledBoard[movedFrom.x][movedFrom.y].g = 128;
			ledBoard[movedFrom.x][movedFrom.y].b = 0;
		}	
		ledBoard[movedTo.x][movedTo.y].r = 128;
		ledBoard[movedTo.x][movedTo.y].g = 0;
		ledBoard[movedTo.x][movedTo.y].b = 0;
	}
	driver.writeToLeds(ledBoard);
	
	/*for(int r = 0; r < 8;  r++){
		for(int c = 0; c < 8; c++){
			ledBoard[moveF.x][moveF.y].r = 0;
			ledBoard[moveF.x][moveF.y].g = 0;
			ledBoard[moveF.x][moveF.y].b = 128;
			ledBoard[moveT.x][moveT.y].r = 0;
			ledBoard[moveT.x][moveT.y].g = 128;
			ledBoard[moveT.x][moveT.y].b = 0;
			if(currBoard[r][c] - prevBoard[r][c] == 1  && r!= moveF.x && r!= moveF.y){
				ledBoard[r][c].r = 0;
				ledBoard[r][c].g = 0;
				ledBoard[r][c].b = 0;
			}
			if((currBoard[r][c] - prevBoard[r][c] == 1  && r!= moveF.x && r!= moveF.y)|| currBoard[r][c] - prevBoard[r][c] == -1){
				ledBoard[r][c].r = 128;
				ledBoard[r][c].g = 0;
				ledBoard[r][c].b = 0;
				driver.writeToLeds(ledBoard);
			}
			//cout << diffBoard[r][c] << " ";
		}
		//cout << endl;
	}*/
	
	return false;
	/*if(currBoard[moveF.x][moveF.y] - prevBoard[moveF.x][moveF.y] == 1 && currBoard[moveT.x][moveT.y] - prevBoard[moveT.x][moveT.y] == -1)
		return true;
	else
		return false;
	*/
}

bool Checkerboard:: checkMoved(Driver &driver, vector<vector<int>> p){
	driver.scan();
	getNewBoard(driver.table);
	
	coord movedFrom {-2, -2};
	coord movedTo {-2, -2};
	int diffArray[8][8];
	bool alreadyMoved = false;
	
	clearLedBoard();
	/*if(p.size() == 1){
		ledBoard[p[0][0]][p[0][1]].r = 0;
		ledBoard[p[0][0]][p[0][1]].g = 0;
		ledBoard[p[0][0]][p[0][1]].b = 128;
		ledBoard[p[0][2]][p[0][3]].r = 0;
		ledBoard[p[0][2]][p[0][3]].g = 128;
		ledBoard[p[0][2]][p[0][3]].b = 0;
	}*/
	showPossibleMoves(driver, p);
	driver.writeToLeds(ledBoard);
	// printCurrBoard();
	// printPrevBoard();
	// cout << endl;
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if(currBoard[r][c] - prevBoard[r][c] == 1){
				movedFrom = {r, c};
				//cout << movedFrom.x << movedFrom.y << endl;
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
		clearLedBoard();
		driver.writeToLeds(ledBoard);
		cout << "transition mode" << endl;
		bool validMove = false;
		for(int r = 0; r < p.size(); r++){
			// if(p[i].size() > 4){
				// for(int c = 0; c < p[r].size(); c+=2){
					// ledBoard[p[c]][p[c+1]].r = 0;
					// ledBoard[p[c]][p[c+1]].g = 0;
					// ledBoard[p[c]][p[c+1]].b = 128;
					// ledBoard[p[c+2]][p[c+3]].r = 0;
					// ledBoard[p[c+2]][p[c+3]].g = 128;
					// ledBoard[p[c+2]][p[c+3]].b = 0;
				// }
			// }
			// else{
				if(p[r][0] == movedFrom.x && p[r][1] == movedFrom.y){
					ledBoard[p[r][0]][p[r][1]].r = 0;
					ledBoard[p[r][0]][p[r][1]].g = 0;
					ledBoard[p[r][0]][p[r][1]].b = 128;
					ledBoard[p[r][2]][p[r][3]].r = 0;
					ledBoard[p[r][2]][p[r][3]].g = 128;
					ledBoard[p[r][2]][p[r][3]].b = 0;
					clearLedBoard();
					driver.writeToLeds(ledBoard);
					validMove = true;
				}	
			// }
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
		
		for(int r = 0; r < p.size(); r++){
			if(p[r][2] == movedTo.x && p[r][3] == movedTo.y){
				validMove = true;
				checkJumped(driver, p, movedFrom, movedTo);
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
	}
	//return false;
}

bool Checkerboard:: checkJumped(Driver &driver, vector<vector<int>> p, coord movedFrom, coord movedTo){
	if(movedFrom.x + 2 == movedTo.x && movedFrom.y + 2 == movedTo.y){ // moved right from top // moved left from bottom
		ledBoard[movedFrom.x+1][movedFrom.y+1].r = 128;
		ledBoard[movedFrom.x+1][movedFrom.y+1].g = 0;
		ledBoard[movedFrom.x+1][movedFrom.y+1].b = 0;
		capturedPiece(driver, movedFrom.x+1, movedFrom.y+1);
	}
	if(movedFrom.x - 2 == movedTo.x && movedFrom.y + 2 == movedTo.y){ 
		ledBoard[movedFrom.x-1][movedFrom.y+1].r = 128;
		ledBoard[movedFrom.x-1][movedFrom.y+1].g = 0;
		ledBoard[movedFrom.x-1][movedFrom.y+1].b = 0;
		driver.writeToLeds(ledBoard);
		capturedPiece(driver, movedFrom.x-1, movedFrom.y+1);
	}
	if(movedFrom.x + 2 == movedTo.x && movedFrom.y - 2 == movedTo.y){
		ledBoard[movedFrom.x+1][movedFrom.y-1].r = 128;
		ledBoard[movedFrom.x+1][movedFrom.y-1].g = 0;
		ledBoard[movedFrom.x+1][movedFrom.y-1].b = 0;
		driver.writeToLeds(ledBoard);
		capturedPiece(driver, movedFrom.x+1, movedFrom.y-1);
	}
	if(movedFrom.x - 2 == movedTo.x && movedFrom.y - 2 == movedTo.y){ // moved left from bottom // moved 
		ledBoard[movedFrom.x-1][movedFrom.y-1].r = 128;
		ledBoard[movedFrom.x-1][movedFrom.y-1].g = 0;
		ledBoard[movedFrom.x-1][movedFrom.y-1].b = 0;
		driver.writeToLeds(ledBoard);
		capturedPiece(driver, movedFrom.x-1, movedFrom.y-1);
	}
	
	return false;
}

void Checkerboard:: capturedPiece(Driver &driver, int r, int c){
	bool pickedUp = false;
	
	while(pickedUp == false){
		driver.scan();
		getNewBoard(driver.table);
		
		if(currBoard[r][c] == 1){
			ledBoard[r][c].r = 0;
			ledBoard[r][c].g = 0;
			ledBoard[r][c].b = 0;
			driver.writeToLeds(ledBoard);
			pickedUp = true;
		}
		
	}
}

/*bool Checkerboard:: checkThinking(int r, int c){
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
}*/
/*
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
*/
