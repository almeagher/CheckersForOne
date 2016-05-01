#ifndef DRIVER_H_
#define DRIVER_H_

#include "lpd8806led.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>
//#include "mux.h"


using namespace std;

typedef struct RGB {
	int r;
	int g;
	int b;
} RGB;

//extern RGB ledBoard[8][8];





class Driver{
	
	private:
	int fd;              /* SPI device file descriptor */
    int leds; /* 75 LEDs in te strand */
  lpd8806_buffer buf;      /* Memory buffer for pixel values */
  RGB temp_color;
  RGB pre_array[8][8];
 
	
	
	
	public:
		Driver();
		Driver(int a);
		
		~Driver();
		
		void writeToLeds(RGB rgbp[8][8]);
		
		void write_color_table(int i,int j, RGB color);
		
		void clear_led();
		
		void setup_pcf();
		void scan();
		void printint();
		int table[8][8];
		bool equal(RGB a, RGB b);
		bool isPlayer1Comp();
		bool isPlayer2Comp();
		
		//vector<vector<bool>> readOccupation(); 
	//	void waitForChange(int timeOutMS);
		//void writeToLeds(RGB rgbp[8][8]);
		
		//vector<vector<bool>> occupiedBoard();

};
#endif
