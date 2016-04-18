#include <cstdlib>
#include <vector>

// file 1 initial
// file 2 player thinking
// file 3 player made move


using namespace std;

typedef struct RGB {
	unsigned byte r;
	unsigned byte g;
	unsigned byte b;
} RGB;

class Game{
	vector<vector<bool> prevBoard; 
	public:
		
		void readOccupation(); 
		
		vector<vector<bool>> lightUpPositions();
		void checkMovement(vector<vector<bool>> newBoard);
		vector<vector<bool>> getPrevBoard();	

}
