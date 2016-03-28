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

class GameState{
	public:
		void Init();
		void Cleanup();
		
		void Pause();
		void Resume();
		
		void HandleEvents();
		void Update();
		void Draw();
		

}
