/*
 * simple_example.c  
 *
 * Copyright 2012 Christopher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 */
#include "lpd8806led.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "Driver.h"
#include <wiringPi.h>
#include <pcf8574.h>

using namespace std;


void setup_mux()
{
	 pcf8574Setup(100,0x27);
	 pcf8574Setup(200,0x26);
	 pcf8574Setup(300,0x25);
	 pcf8574Setup(400,0x24);
	 pcf8574Setup(500,0x23);
	 pcf8574Setup(600,0x22);
	 pcf8574Setup(700,0x21);
	 pcf8574Setup(800,0x20);
}

void input_pin()
{
	 for(int i=0;i<8;i++) pinMode(100+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(200+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(300+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(400+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(500+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(600+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(700+i,INPUT);
	 for(int i=0;i<8;i++) pinMode(800+i,INPUT); 
}




int main(int argc, char *argv[]) {
	
	//initial LED//////////////////////////////////////
	//////////////////////////////////
	////////////////////////////////////
	///////////////////////////////////
  int fd;              /* SPI device file descriptor */
  const int leds = 75; /* 75 LEDs in te strand */
  lpd8806_buffer buf;      /* Memory buffer for pixel values */
  int count;           /* Count of iterations (up to 3) */
  int i;               /* Counting Integer */
  set_gamma(2.5,2.5,2.5);
  RGB red;
  red.r=255;
  red.g=0;
  red.b=0;
  
  Driver driver;
  /* Open SPI device */
  fd = open("/dev/spidev0.0",O_WRONLY);
  if(fd<0) {
      /* Open failed */
      fprintf(stderr, "Error: SPI device open failed.\n");
      exit(1);
  }

  /* Initialize SPI bus for lpd8806 pixels */
  if(spi_init(fd)<0) {
      /* Initialization failed */
      fprintf(stderr, "Unable to initialize SPI bus.\n");
      exit(1);
  }

  /* Allocate memory for the pixel buffer and initialize it */
  if(lpd8806_init(&buf,leds)<0) {
      /* Memory allocation failed */
      fprintf(stderr, "Insufficient memory for pixel buffer.\n");
      exit(1);
  }

  /* Loop Forever */
  
  for(i=0;i<leds;i++) {
    
      write_gamma_color(&buf.pixels[i],0x00,0x00,0x00);
      
  }
  
  
    send_buffer(fd,&buf);
  /* Although the program never gets to this point, below is how to clean up */

  /* Free the pixel buffer */
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  
  
	//initial MUX
	//
	//
	
	



  
  while(1)
			{
				int h;
				int l;
				int j;
				printf("which led you wanna light up\n");
				scanf("%d",&h);
				scanf("%d",&l);
				
				printf("%d he %d", h,l);
				driver.write_color_table(h,l,buf,red);
				send_buffer(fd,&buf);
				
				printf("lear?");
				scanf("%d",&j);
				if(j==1)  {driver.clear_led(buf,leds);
					send_buffer(fd,&buf);}
				
  
			}
  
  
for(i=0;i<leds;i++) {
    
      write_gamma_color(&buf.pixels[i],0x00,0x00,0x00);
      
  }
    send_buffer(fd,&buf);
  /* Although the program never gets to this point, below is how to clean up */

  /* Free the pixel buffer */
  lpd8806_free(&buf);

  /* Close the SPI device */
  close(fd);

  return 0;
}
