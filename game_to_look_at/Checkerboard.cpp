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
	
	bool done = true;
	
	for(int r = 0; r < 8; r++){
		for(int c = 0; c < 8; c++){
			if(currBoard[r][c] - arr[r][c] == -1){
				ledBoard[r][c].r = 128;
				ledBoard[r][c].g = 0;
				ledBoard[r][c].b = 0;
				
				driver.writeToLeds(ledBoard);
				done = false;
			}
			if(currBoard[r][c] - arr[r][c] == 1){
				ledBoard[r][c].r = 64;
				ledBoard[r][c].g = 64;
				ledBoard[r][c].b = 64;
				
				driver.writeToLeds(ledBoard);
				done = false;
			}
			if(currBoard[r][c] - arr[r][c] == 0){
				ledBoard[r][c].r = 0;
				ledBoard[r][c].g = 0;
				ledBoard[r][c].b = 0;
				driver.writeToLeds(ledBoard);
			}
			
		}
	}
	if(done == false)
		return false;
	clearLedBoard();
	driver.writeToLeds(ledBoard);
	changeBoard();
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

void Checkerboard:: setToError(int r, int c){
	ledBoard[r][c].r = 128;
	ledBoard[r][c].g = 0;
	ledBoard[r][c].b = 0;
}

void Checkerboard:: possDest(int r, int c){
	ledBoard[r][c].r = 0;
	ledBoard[r][c].g = 128;
	ledBoard[r][c].b = 0;
}

void Checkerboard:: possSource(int r, int c){
	ledBoard[r][c].r = 0;
	ledBoard[r][c].g = 0;
	ledBoard[r][c].b = 128;
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

vector<int> Checkerboard:: getMoveMade(Driver &driver, vector<vector<int>> p, coord moveF, coord moveT){
	for(int i = 0; i < p.size(); i++){
		if(p[i][0] == moveF.x && p[i][1] == moveF.y && p[i][p[i].size()-2] == moveT.x && p[i][p[i].size()-1] == moveT.y){
			return p[i];
		}
	}
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
			//cout << "can move multiple" << endl;
			possSource(p[r][0],p[r][1]);
			for(int c = 2; c < p[r].size()-3; c+=2){
				ledBoard[p[r][c]][p[r][c+1]].r = 128;
				ledBoard[p[r][c]][p[r][c+1]].g = 128;
				ledBoard[p[r][c]][p[r][c+1]].b = 0;
				possDest(p[r][c+2],p[r][c+3]);
			}
		}
		else{
			possSource(p[r][0], p[r][1]);
			possDest(p[r][2], p[r][3]);
		}
	}
	driver.writeToLeds(ledBoard);
}



bool Checkerboard:: waitUntilMoved(Driver &driver, coord moveF, coord moveT, vector<vector<int>> p){
	/*driver.scan();
	getNewBoard(driver.table);
	int diffBoard[8][8];
	
	if(currBoard[moveF.x][moveF.y] - prevBoard[moveF.x][moveF.y] == 1 && currBoard[moveT.x][moveT.y] - prevBoard[moveT.x][moveT.y] == -1){
		changeBoard();
		clearLedBoard();
		driver.writeToLeds(ledBoard);
		
		checkJumped(driver, createVector(moveF, moveT), moveF, moveT);
		return true;
	}*/
	while(checkMoved(driver, p) == false){
		
	}
	return true;
	/*
	
	
	bool alreadyMoved = false;
	if(alreadyShowingMoves == false){	
		clearLedBoard();
		driver.writeToLeds(ledBoard);
	}
	
	coord movedFrom {-2, -2};
	coord movedTo {-2, -2};
	int diffArray[8][8];
	bool validMove = false;
	clearLedBoard();
	possSource(moveF.x, moveF.y);
	//possDest(moveT.x, moveT.y);
	ledBoard[moveT.x][moveT.y].r = 128;
	ledBoard[moveT.x][moveT.y].g = 0;
	ledBoard[moveT.x][moveT.y].b = 128;
	
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
		if(alreadyShowingMoves == false){
			showPossibleMoves(driver, p);
			alreadyShowingMoves = true;
		}
		return false;
	}
	else if(movedTo.x == -2 && movedTo.y == -2){
		cout << "transition mode AI" << endl;
		clearLedBoard();
		driver.writeToLeds(ledBoard);
		alreadyShowingMoves = false;
		bool validMove = false;
		bool multiplePlacesCanMove = false;
		for(int r = 0; r < p.size(); r++){
			if(p[r].size() > 4){
				cout << "inside this" << endl;
				possSource(p[r][0], p[r][1]);
				possDest(p[r][p[r].size()-2], p[r][p[r].size()-1]);
			}
			else{
				if(p[r][0] == movedFrom.x && p[r][1] == movedFrom.y){
					possSource(p[r][0],p[r][1]);
					possDest(p[r][2], p[r][3]);
					validMove = true;
				}	
			}
		}
		
		if(validMove == false){
			cout << "validMove == false" << endl;
			setToError(movedFrom.x,movedFrom.y);
			//driver.writeToLeds(ledBoard);	
		}
		
		driver.writeToLeds(ledBoard);
		return false;	
		/*if(movedFrom.x == moveF.x && movedFrom.y == moveF.y){
			checkJumped(driver, createVector(moveF, moveT), moveF, moveT);
			validMove = true;
		}
		if(validMove == false){
			setToError(movedFrom.x, movedFrom.y);
			driver.writeToLeds(ledBoard);	
		}
	}
	else{
		alreadyShowingMoves = false;
		for(int r = 0; r < p.size(); r++){
			if(p[r].size() > 4){
				cout << "put down and multiple moves" << endl;
				
				if(p[r][p[r].size()-2] == movedTo.x && p[r][p[r].size()-1]){
					cout << "put piece down at final destination" << endl;
					getRidOfPieces(driver, p[r]);
					validMove = true;
					return true;
					cout << "valid move = true" << endl; 
				}
			}
			else{
				if(p[r][2] == movedTo.x && p[r][3] == movedTo.y){
					validMove = true;
					changeBoard();
					
					checkJumped(driver, p, movedFrom, movedTo);
					clearLedBoard();
					driver.writeToLeds(ledBoard);
					return true;
				}
			}
		}
		if(validMove == false){
			possSource(movedFrom.x,movedFrom.y);
			setToError(movedTo.x, movedTo.y);
			cout << "moved and validMove = false" << endl;
			driver.writeToLeds(ledBoard);	
			return false;
		}
		
		//return false;
		
		if(!(movedFrom.x == moveF.x && movedFrom.y == moveF.y)){
			ledBoard[movedFrom.x][movedFrom.y].r = 128;
			ledBoard[movedFrom.x][movedFrom.y].g = 128;
			ledBoard[movedFrom.x][movedFrom.y].b = 0;
		}	
		setToError(movedTo.x, movedTo.y);
	}
	driver.writeToLeds(ledBoard);
	
	
	return false;*/
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
	if(alreadyShowingMoves == false){	
		clearLedBoard();
		driver.writeToLeds(ledBoard);
	}
	
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
	
	if(movedFrom.x == -2 && movedFrom.y == -2 && movedTo.x == -2 && movedTo.y == -2){ // put piece down in same spot
		if(alreadyShowingMoves == false){
			showPossibleMoves(driver, p);
			alreadyShowingMoves = true;
		}
		return false;
	}
	
	else if(movedTo.x == -2 && movedTo.y == -2){
		clearLedBoard();
		driver.writeToLeds(ledBoard);
		alreadyShowingMoves = false;
		cout << "transition mode" << endl;
		bool validMove = false;
		bool multiplePlacesCanMove = false;
		for(int r = 0; r < p.size(); r++){
			if(p[r].size() > 4){
				cout << "inside this" << endl;
				possSource(p[r][0], p[r][1]);
				possDest(p[r][p[r].size()-2], p[r][p[r].size()-1]);
				/*for(int c = 0; c < p[r].size()-2; c+=2){
					cout << "what about here" << endl;
					possSource(p[r][c], p[r][c+1]);
					possDest(p[r][c+2], p[r][c+3]);
				}*/
			}
			else{
				if(p[r][0] == movedFrom.x && p[r][1] == movedFrom.y){
					if(multiplePlacesCanMove == false){
						clearLedBoard();
						driver.writeToLeds(ledBoard);	
					}
					possSource(p[r][0],p[r][1]);
					possDest(p[r][2], p[r][3]);
					multiplePlacesCanMove = true;
					//clearLedBoard();
					//driver.writeToLeds(ledBoard);
					validMove = true;
				}	
			}
		}
		
		if(validMove == false){
			//cout << "validMove == false" << endl;
			setToError(movedFrom.x,movedFrom.y);
			//driver.writeToLeds(ledBoard);	
		}
		
		driver.writeToLeds(ledBoard);
		return false;		
	}
	/*else if(alreadyMoved == true){
		cout << "error state" << endl;
	}*/
	else{
		alreadyShowingMoves = false;
		cout << movedFrom.x << " " << movedFrom.y << " -> " << movedTo.x << " " << movedTo.y << endl;
		pieceMoved = to_string(movedFrom.x) + " " + to_string(movedFrom.y) + " " + to_string(movedTo.x) + " " + to_string(movedTo.y) + " -1";
		bool validMove = false;
		
		/*for(int r = 0; r < p.size(); r++){
			if(p[r][2] == movedTo.x && p[r][3] == movedTo.y){
				validMove = true;
				checkJumped(driver, p, movedFrom, movedTo);
				return true;
			}	
		}*/
		for(int r = 0; r < p.size(); r++){
			if(p[r].size() > 4){
				cout << "put down and multiple moves" << endl;
				cout << p[r][0] << " " << movedFrom.x << ", " << p[r][1] << " " << movedFrom.y << ", " << p[r][p[r].size()-2] << " " << movedTo.x << ", " << p[r][p[r].size()-1] << " " << movedTo.y << endl;
				if(p[r][0] == movedFrom.x && p[r][1] == movedFrom.y && p[r][p[r].size()-2] == movedTo.x && p[r][p[r].size()-1] == movedTo.y){
					cout << "put piece down at final destination" << endl;
					getRidOfPieces(driver, p[r]);
					validMove = true;
					return true;
					cout << "valid move = true" << endl; 
				}
			}
			else{
				if(p[r][0] == movedFrom.x && p[r][1] == movedFrom.y && p[r][2] == movedTo.x && p[r][3] == movedTo.y){
					cout << "got inside else if statement" << endl;
					validMove = true;
					changeBoard();
					
					checkJumped(driver, p, movedFrom, movedTo);
					//getRidOfPieces(driver, p[r]);
					clearLedBoard();
					driver.writeToLeds(ledBoard);
					return true;
				}
			}
		}
		if(validMove == false){
			possSource(movedFrom.x,movedFrom.y);
			setToError(movedTo.x, movedTo.y);
			cout << "moved and validMove = false" << endl;
			driver.writeToLeds(ledBoard);	
			return false;
		}
		
		return false;
	}
	return false;
}

bool Checkerboard:: checkJumped(Driver &driver, vector<vector<int>> p, coord movedFrom, coord movedTo){
	for(int i = 0; i < p.size(); i++){
		if(p[i].size() > 4){
			for(int j = 0; j < p[i].size(); j+=2){
				if(p[i][j] == movedFrom.x && p[i][j+1] == movedFrom.y && p[i][p[i].size()-2] == movedTo.x && p[i][p[i].size()-1] == movedTo.y){
					cout << "double jump or more" << endl;
					
				}
			}
		}
		else{
			int capturedX = movedFrom.x - (movedFrom.x - movedTo.x)/2;
			int capturedY = movedFrom.y - (movedFrom.y - movedTo.y)/2;
			if(currBoard[capturedX][capturedY] == 0){
				setToError(capturedX, capturedY);
				driver.writeToLeds(ledBoard);
				capturedPiece(driver, capturedX, capturedY);
			}
			//else cout << "not capturable" << endl;
			
		}
	}
		
	return false;
}

void Checkerboard:: getRidOfPieces(Driver &driver, vector<int> p){
	vector<coord> toGetRidOf;
	pieceMoved = "";
	for(int i = 0; i < p.size(); i++){
		pieceMoved += to_string(p[i]) + " ";
	}
	pieceMoved += "-1";
	cout << "PieceMoved: " << pieceMoved << endl;
	
	
	for(int i = 0; i < p.size()-2; i+=2){
		int capturedX = p[i] - (p[i] - p[i+2])/2;
		int capturedY = p[i+1] - (p[i+1] - p[i+3])/2;
		cout << capturedX << " " << capturedY << endl;
		setToError(capturedX, capturedY);
		coord m = {capturedX, capturedY};
		toGetRidOf.push_back(m);
	}
	driver.writeToLeds(ledBoard);
	
	for(int i = 0; i < toGetRidOf.size(); i++){	
		cout << "about to capture " << endl;
		capturedPiece(driver, toGetRidOf[i].x, toGetRidOf[i].y);
	}
	clearLedBoard();
	driver.writeToLeds(ledBoard);
	changeBoard();
}

void Checkerboard:: capturedPiece(Driver &driver, int r, int c){
	bool pickedUp = false;
	//cout << "inside " << endl;
	while(pickedUp == false){
		driver.scan();
		getNewBoard(driver.table);
		
		if(currBoard[r][c] == 1){
			clearLedBoard();
			driver.writeToLeds(ledBoard);
			changeBoard();
			pickedUp = true;
		}
		
	}
}

