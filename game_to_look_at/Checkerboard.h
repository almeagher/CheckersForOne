#include <cstdlib>
#include <vector>

using namespace std;

typedef struct RGB {
	unsigned int r;
	unsigned int g;
	unsigned int b;
} RGB;

class Checkerboard{
	// if h v c, human is bottom - red, comp is yellow
	// if h v h, red goes first
   public:
   char newPieceType = ' ';
   // vector <vector <int>> board(8, vector<int>(8));
   // vector <vector <int>> board;
   // vector <vector <int>> prevBoard;
   char prevBoard[8][8];
   char board[8][8];
   
   
   Checkerboard();
   void printBoard();
	// void setPieces();
	void getNewBoard(int newBoard[8][8]);
	char getPieceType(int r, int c);
	void checkMoved();
	void showPossibleMoves(int r, int c);
	bool checkThinking(int r, int c);
	bool checkMovedLeft(int r, int c);
	bool checkMovedRight(int r, int c);	
	bool checkValidMove(char pieceType, int r, int c);
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
