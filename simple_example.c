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
  
  void write_color_table(int i,int j,lpd8806_buffer buf)
  {
	  if(j%2==0)
	  {
		  write_gamma_color(&buf.pixels[j*8+i],255,0,0);
	  }
	  else if (j&2!=0)
		  
	  {
		  write_gamma_color(&buf.pixels[(j+1)*8-1-i],255,0,0);
	  }
  }
  

int main(int argc, char *argv[]) {
  int fd;              /* SPI device file descriptor */
  const int leds = 500; /* 50 LEDs in the strand */
  lpd8806_buffer buf;      /* Memory buffer for pixel values */
  int count;           /* Count of iterations (up to 3) */
  int i;               /* Counting Integer */
  set_gamma(2.5,2.5,2.5);
  int color_table[8][8];
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
  
  
  write_color_table(3,2,buf);
  
  
  if(send_buffer(fd,&buf)<0) {
        fprintf(stderr, "Error sending data.\n");
        exit(1);
      }


  

  /* Loop Forever */
 
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
