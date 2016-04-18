#include <iostream>
#include <cstdlib>
#include <vector>
#include "Checkerboard.h"

using namespace std;

vector <vector<RGB>> lightBoard(vector<vector<int>> board){
	
	
	vector<vector<RGB>> lightBoard;
	RGB black = { 0, 0, 0}
	RGB green = { 0, 255, 0}
	for(int r = 0; r < board.size(); r++){
		for(int c = 0; c < board.size(); c++){
			if(board[r][c] == 1)
				lightBoard[r][c] = green;
			else
				lightBoard[r][c] = black;
		}
	}
	return lightBoard;
}

int main(int argc, char *argv[]) {
	Driver driver;
	vector<vector<int>> reedBoard = driver.getPositions();
	
	driver.writeToLeds(lightBoard(reedBoard));
}