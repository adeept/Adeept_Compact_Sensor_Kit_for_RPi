/*
* File name   : main.c
* Description : Read voltage from ADC0832, and display on segment display
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2016/06/18
*/
#include "segment.h"
#include "ADC0832.h"
#include <stdio.h>

int main(void)
{
	uchar tmp;
	float vol;

	if(wiringPiSetup() < 0){
		printf("wiringPi setup failed!\n");
		return -1;
	}

	TM1638_init();
	ADC0832_Init();
	numberDisplay(1234);
	delay(2000);

	while(1){
		tmp = get_ADC_Result();
		vol = 5.0/255 * tmp;
		printf("voltage : %.2fV\n", vol);
		numberDisplay_dec(vol);
		delay(100);
	}

	return 0;
}
