#include <cstdlib>
#include <vector>

using namespace std;

typedef struct RGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGB;

class Checkerboard{
	// if h v c, human is bottom - red, comp is yellow
	// if h v h, red goes first
   public:
   // vector <vector <int>> board(8, vector<int>(8));
   vector <vector <int>> prevBoard;
   vector <vector <int>> board;
   Checkerboard();
   void printBoard();
	// void setPieces();
	void getNewMove(vector<vector<bool>> newBoard);
	
	bool checkValidMove();
	
	bool checkMovedLeft();
	bool checkMovedRight();
	bool checkJumped();
	
	void checkState();
	void moveState();
	void transitionState();
	void errorState();
	
	void getPossibleMoves();
	void computerMove();
	
	vector<vector<RGB>> lightUpBoard();
};
