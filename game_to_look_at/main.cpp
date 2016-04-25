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
	// vector<vector <bool>> test (8, vector<bool>(8));
	// ifstream file;
	// file.open("file2.txt");
	char test[8][8] = {{'0'}};
	
	// while(!file.eof()){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				// int x;
				cin >> test[i][j];
				// cout << test[i][j] << " ";
				// test[i][j] = x;
			}
			// cout << endl;
		}
	// }
	cout << endl << endl;
	// cerr << test[0][0];

	Checkerboard* cb = new Checkerboard;
	// cb->setPieces();
	cb->getNewBoard(test);
	cb->checkMoved();
	cb->printBoard();
	cb->printLED();
   return 0;
}

