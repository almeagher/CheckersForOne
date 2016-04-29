#include <cstdlib>
#include "Checkerboard.h"
#include <iostream>
#include "Driver.h"
#include "game.h"

using namespace std;
//extern Driver driver;

void endEarly(bool endEarly){
	if(endEarly == true){
		// delete current board game
		
	}
}

int main(int argc, char** argv) {
	bool player1 = true;
	bool player2 = false;
	
	Checkerboard cb = Checkerboard();
	long a = 0;
	Driver driver = Driver();
	//player1 = driver.isPlayer1Comp();
	//player2 = driver.isPlayer2Comp();
	game checkers;
	checkers.playTheGame(player1, player2, driver, cb);
	// cb->setPlayers(player1, player2, driver);
	
	/*RGB ledBoard[8][8];
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			ledBoard[i][j].r = 0;
			ledBoard[i][j].g = 0;
			ledBoard[i][j].b = 0;
		}
	}
	
	driver.writeToLeds(ledBoard);
	*/
	
	//char test[8][8] = {{'0'}};
	
	// for(int i = 0; i < 8; i++){
		// for(int j = 0; j < 8; j++){
		// cin >> test[i][j];
		// }
	// }

	// driver.scan(); 
	// cb->getNewBoard(driver.table);
	// cb->printBoard();
	// cb->printLED();
   return 0;
}

