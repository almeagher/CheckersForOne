#include <cstdlib>
#include <vector>

using namespace std;

typedef struct RGB {
	unsigned byte r;
	unsigned byte g;
	unsigned byte b;
} RGB;

class Driver{
	
	public:
		
		vector<vector<bool>> readOccupation(); 
		void waitForChange(int timeOutMS);
		void writeToLeds(vector<vector<RGB>> lightPositions);
		
		vector<vector<bool>> occupiedBoard();

}
