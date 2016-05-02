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
	
	Driver driver = Driver();
	driver.scan();
	Checkerboard cb = Checkerboard(driver.table);
	//driver.printint();
	
	RGB ledBoard[8][8];
	//driver.clear_led();
	while(cb.canStart(driver) == false){
		
	}
	bool player1 = driver.isPlayer1Comp();
	bool player2 = driver.isPlayer2Comp();
	game checkers;
	checkers.playTheGame(player1, player2, driver, cb);
	
	return 0;
}

