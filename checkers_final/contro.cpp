#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 
#include <iostream> 	
#include <signal.h>

int main(int argc, char *argv[]) {


	wiringPiSetupGpio();
	pinMode(26,INPUT);
	pullUpDnControl(26, PUD_UP);
	

	
	while(1)
	{
	int pid= fork();
	if(pid == 0)
	{
		execvp("./462/game",argv);
	}
	
	else
	{
		while (1)
		{
			
			usleep(100000);
			if(digitalRead(26)==0)
				{
				printf("starting to end the process");
				kill(pid,SIGKILL);
				while(digitalRead(26)==0)
					{}
				
				break;
				
				}
			
			
			
		}
	}
}




}
