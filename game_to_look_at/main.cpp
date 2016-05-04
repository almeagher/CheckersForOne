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
	cout<<"start\n";
	wiringPiSetupGpio();
	pinMode(16,INPUT);
	pullUpDnControl(16, PUD_UP);
	
	pinMode(19,INPUT);
	pullUpDnControl(19, PUD_UP);
	
	int p1= digitalRead(19);
	int p2= digitalRead(16);
	
	Driver driver = Driver();
	driver.scan();
	Checkerboard cb = Checkerboard(driver.table);
	
	RGB ledBoard[8][8];
	driver.clear_led();
	while(cb.canStart(driver) == false){
		
	}
	
	
	bool player1 = false;
	bool player2 = false;
	if(p1 == 1) player1=true;
	if(p2 == 1) player2=true;
	
	cout << "P1: " << player1 << endl;
	cout << "P2: " << player2 << endl;
	game checkers;
	checkers.playTheGame(player1, player2, driver, cb);
	
	return 0;
}

