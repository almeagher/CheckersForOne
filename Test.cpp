#include <iostream>
#include <cstdlib>
#include <vector>
// #include "Checkerboard.h"
#include "Driver.cpp"

using namespace std;

RGB ledBoard[8][8];

void lightBoard(int board[8][8]){
	
	RGB black = { 0, 0, 0};
	RGB green = { 0, 255, 0};
	
	for(unsigned r = 0; r < 8; r++){
		for(unsigned c = 0; c < 8; c++){
			if(board[r][c] == 1)
				ledBoard[r][c] = green;
			else
				ledBoard[r][c] = black;
		}
	}
	// return lightBoard;
}

int main(int argc, char *argv[]) {
	Driver driver;
	
	driver.setup_pcf();
	driver.scan();
	while(1){
		driver.scan();
		int reedBoard[8][8] = driver.getPositions();
		lightBoard(reedBoard)
		driver.writeToLeds(ledBoard));
		
	}
	
}