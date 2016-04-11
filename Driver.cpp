#include "Driver.h"


void Driver::write_color_table(int i,int j,lpd8806_buffer buf,RGB color)
 {
	  if(j%2==0)
	  {
	
		  write_gamma_color(&buf.pixels[j*8+i],color.r,color.g,color.b);
	  }
	  else if (j%2!=0)
		  
	  {
		  
		  write_gamma_color(&buf.pixels[(j+1)*8-1-i],color.r,color.g,color.b);
	  }
  }
  
  

void Driver::writeToLeds(RGB rgbp[8][8],lpd8806_buffer buf, RGB color)
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8;j++)
		{
			RGB color = rgbp[i][j];
			write_color_table(i,j, buf, color);
			
		}
}
}

void Driver::clear_led(lpd8806_buffer buf,const int leds)
{
	for(int i=0;i<leds;i++) {
    
      write_gamma_color(&buf.pixels[i],0x00,0x00,0x00);
      
  }
}
