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
   char newPieceType = "";
   // vector <vector <int>> board(8, vector<int>(8));
   vector <vector <int>> board;
   Checkerboard();
   void printBoard();
	// void setPieces();
	void getNewBoard(vector<vector<bool>> newBoard);
	void checkValidMove();
	void checkIfPlayerMadeMove();
	void checkIfPlayerThinking();
	void getPossibleMoves();
	void computerMove();
	
	vector<vector<RGB>> lightUpBoard();
};
