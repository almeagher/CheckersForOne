#include "Driver.h"

Driver :: ~Driver()
{
	//clear();
	/* Free the pixel buffer */
	lpd8806_free(&buf);

	/* Close the SPI device */
	close(fd);
}

 Driver::Driver( int a)
 {
	 printf("gg");
 }

 Driver::Driver()
{
	
	setup_pcf();
	set_gamma(2.5,2.5,2.5);
	leds= 64;
		
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
	
	for(int i=0;i<leds;i++) {
		
		write_gamma_color(&buf.pixels[i],0x00,0x00,0x00);
			
	}
	
	
		send_buffer(fd,&buf);

}

void Driver::write_color_table(int i,int j,RGB color)
 {
	if(j%2==0)
	{

		write_gamma_color(&buf.pixels[j*8+i],color.r,color.g,color.b);
	}
	else if (j%2!=0)
		
	{
		
		write_gamma_color(&buf.pixels[(j+1)*8-1-i],color.r,color.g,color.b);
	}
	
	send_buffer(fd,&buf);
}
	
bool Driver::equal(RGB a, RGB b){
	if(a.r==b.r && a.b==b.b && a.g==b.g) return true;
	else return false;
}
	
	

void Driver::writeToLeds(RGB rgbp[8][8])
{
	//clear_led();
	
	
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8;j++)
		{
			if(!equal(pre_array[i][j],rgbp[i][j]))
			{
				temp_color = rgbp[i][j];
				write_color_table(j,i, temp_color);
			}
		}
}

for(int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			pre_array[i][j]=rgbp[i][j];
		}
	}
}

void Driver::clear_led()
{
	for(int i=0;i<leds;i++) {
		
			write_gamma_color(&buf.pixels[i],0x00,0x00,0x00);
			
	}
	send_buffer(fd,&buf);
}

void Driver::scan()
{
	for(int i=1;i<9;i++)
	{
		for (int j=0;j<8;j++)
		{
			table[i-1][j]=digitalRead(100*i+j);
		}
	}
}

void Driver::printint()
{
	for(int i=0;i<8; i++)
	{
		for(int j=0;j<8;j++)
		{
			printf("%d ",table[i][j]);
			
		}
		printf("\n");
	}
}
void Driver::setup_pcf()
{

	pcf8574Setup(100,0x20);
	pcf8574Setup(200,0x21);
	pcf8574Setup(300,0x22);
	pcf8574Setup(400,0x23);
	pcf8574Setup(500,0x24);
	pcf8574Setup(600,0x25);
	pcf8574Setup(700,0x26);
	pcf8574Setup(800,0x27);
	for(int i=1; i<9;i++)
	{
		for (int j=0; j<8;j++)
			{
				pinMode(i*100+j,INPUT);
			}
		
	}
	
}

bool Driver:: isPlayer1Comp(){
	return true;
}

bool Driver:: isPlayer2Comp(){
	return false;
}
