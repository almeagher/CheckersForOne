#include <cstdlib>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>

#include <ctime>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <cassert>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>


#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <unistd.h>
#include <time.h>


#include <ctime>
#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "lpd8806led.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>

using namespace std;

typedef struct RGB {
	int r;
	int g;
	int b;
} RGB;







class Driver{
	
	public:
		void writeToLeds(RGB rgbp[8][8],lpd8806_buffer buf,RGB color);
		
		void write_color_table(int i,int j,lpd8806_buffer buf, RGB color);
		
		void clear_led(lpd8806_buffer buf,const int leds);
		//vector<vector<bool>> readOccupation(); 
	//	void waitForChange(int timeOutMS);
		//void writeToLeds(RGB rgbp[8][8]);
		
		//vector<vector<bool>> occupiedBoard();

};
