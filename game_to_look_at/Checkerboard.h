#include <cstdlib>
#include <vector>
#include <string>
#include "Driver.h"

#ifndef CHECKERBOARD_H_
#define CHECKERBOARD_H_

using namespace std;

typedef struct coord {
	int x;
	int y;
} coord;

class Checkerboard{
public:
	string pieceMoved;
	
	int prevBoard[8][8];
	int currBoard[8][8];

	Checkerboard();
	Checkerboard(int b[8][8]);
	bool canStart(Driver &driver);
		
	void printCurrBoard();
	void printPrevBoard();
	void printLedBoard();
	void clearLedBoard();
	
	void changeBoard();
	void getNewBoard(int newBoard[8][8]);
	
	string getPieceMoved();
	vector<vector<int>> createVector(coord mf, coord mt);
	void showPossibleMoves(Driver &driver, vector<vector<int>> p);
	
	bool waitUntilMoved(Driver &driver, coord mf, coord mt);
	bool checkMoved(Driver &driver, vector<vector<int>> p);
	bool checkJumped(Driver &driver, vector<vector<int>> p, coord mf, coord mt);
	void capturedPiece(Driver &driver, int r, int c);
	
	/*
	coord fromPiece;
	bool isEnd = false;
	coord getFromPiece();
	void setFromPiece(int r, int c);
	bool checkThinking(int r, int c);
	void checkState();
	void moveState();
	void transitionState();
	void errorState();
		
	void checkIfPlayerMadeMove();
	void checkIfPlayerThinking();
	void getPossibleMoves();
	void computerMove();

	int** lightUpBoard();
	*/
	
};
#endif
