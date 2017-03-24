/*
* File name   : touchBtn.c
* Description : Toggle a led by a touch button.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/05
*/
#include <wiringPi.h>
#include <stdio.h>

#define LedPin    0
#define ButtonPin 1

int status = 1;

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(LedPin, OUTPUT); 
	pinMode(ButtonPin, INPUT);

	pullUpDnControl(ButtonPin, PUD_DOWN);

	while(1){
		if(digitalRead(ButtonPin) == 1){
			delay(10);
			if(digitalRead(ButtonPin) == 1){
				status = !status;
				digitalWrite(LedPin, status);   //toggle the status of led	
				printf("The status of led is toggled !\n");
			}
			while(!!digitalRead(ButtonPin));
		}
	}

	return 0;
}
