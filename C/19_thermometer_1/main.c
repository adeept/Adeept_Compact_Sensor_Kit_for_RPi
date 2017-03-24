/*
* File name   : main.c
* Description : Read the temperature from DS18b20, and display on segment display
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2016/06/18
*/
#include "segment.h"
#include "ds18b20.h"
#include <stdio.h>

int main(void)
{
	float tmp;

	if(wiringPiSetup() < 0){
		printf("wiringPi setup failed!\n");
		return -1;
	}

	TM1638_init();
	numberDisplay(1234);
	delay(2000);

	while(1){
		tmp = ds18b20Read();
		numberDisplay_dec(tmp);
		delay(500);
	}

	return 0;
}
