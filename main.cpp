#include <cstdlib>
#include "Checkerboard.h"
#include <iostream>

using namespace std;

void numOfPlayers(bool aiPlayer){
	if(aiPlayer == true){
		// human vs computer
		// human starts
		// human red pieces
	}
	else{
		// human vs human 
		// player using red pieces goes first
	}
}

void endEarly(bool endEarly){
	if(endEarly == true){
		// delete current board game
		
	}
}

int main(int argc, char** argv) {
	vector<vector <bool>> test (8, vector<bool>(8));
	// ifstream file;
	// file.open("file2.txt");
	
	// while(!file.eof()){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				bool x;
				cin >> x;
				test[i][j] = x;
			}
		}
	// }
	cerr << test[0][0];
	Checkerboard* cb = new Checkerboard();
	cb->printBoard();
	// cb->setPieces();
	cb->getNewBoard(test);
	
   return 0;
}

