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
	bool player1 = true;
	bool player2 = false;
	Checkerboard* cb = new Checkerboard;
	cb->setPlayers(player1, player2);
	char test[8][8] = {{'0'}};
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cin >> test[i][j];
		}
	}

	
	cb->getNewBoard(test);
	cb->checkMoved();
	cb->printBoard();
	cb->printLED();
   return 0;
}

