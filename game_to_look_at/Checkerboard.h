#include <cstdlib>
#include <vector>
#include <string>
#include "Driver.h"
//#include "board.h"
//#include "game.h"

#ifndef CHECKERBOARD_H_
#define CHECKERBOARD_H_

using namespace std;

/*typedef struct RGB {
	int r;
	int g;
	int b;
} RGB;*/

typedef struct coord {
	int x;
	int y;
} coord;

class Checkerboard{
public:
	bool isEnd = false;
	string pieceMoved;
	coord fromPiece;
	//bool validMove = false;
	int prevBoard[8][8];
	int currBoard[8][8];
	//RGB ledBoard[8][8];
	
	// error = {128, 0, 0};
	//RGB possible = {0,128, 0};
	//RGB blank = {0,0, 0};

	Checkerboard();
	Checkerboard(int b[8][8]);
	void printBoard();
	void printLED();
	
	void changeBoard();
	
	void getNewBoard(int newBoard[8][8]);
	coord getFromPiece();
	void setFromPiece(int r, int c);
	//bool checkIfValidMove();
	//void setValidMoveVar(bool value);
	
	bool checkMoved(Driver &driver, vector<int> p);
	string getPieceMoved();
	void showPossibleMoves(int r, int c);
	bool checkThinking(int r, int c);

	// bool checkValidMove(char pieceType, int r, int c);
	bool checkJumped(int r, int c);
	void checkState();
	void moveState();
	void transitionState();
	void errorState();
		
	void checkIfPlayerMadeMove();
	void checkIfPlayerThinking();
	void getPossibleMoves();
	void computerMove();

	int** lightUpBoard();
};
#endif
