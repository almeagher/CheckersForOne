#include <cstdlib>
#include <vector>
#include "board.h"
#include "game.h"

using namespace std;

typedef struct RGB {
	int r;
	int g;
	int b;
} RGB;

typedef struct coord {
	int x;
	int y;
} coord;

class Checkerboard{
public:
	bool isEnd = false;
	game checkers;
	
	void setPlayers(bool p1, bool p2);
	
	char prevBoard[8][8];
	char board[8][8];
	RGB ledBoard[8][8];
	
	RGB error = {128, 0, 0};
	RGB possible = {0,128, 0};
	RGB blank = {0,0, 0};

	Checkerboard();
	void printBoard();
	void printLED();
	
	void getNewBoard(char newBoard[8][8]);
	// char getPieceType(int r, int c);
	void checkMoved();
	void showPossibleMoves(int r, int c);
	bool checkThinking(int r, int c);
	// bool checkMovedLeft(int r, int c);
	// bool checkMovedRight(int r, int c);	
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
