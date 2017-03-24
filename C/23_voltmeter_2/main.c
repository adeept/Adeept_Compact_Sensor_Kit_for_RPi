/*
* File name   : main.c
* Description : Read voltage from ADC0832, and display on LCD1602
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2016/06/18
*/
#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>

#include <stdio.h>
#include <stdlib.h>

#include "ADC0832.h"

#define        AF_BASE              64
#define        AF_RS      (AF_BASE + 0)
#define        AF_RW      (AF_BASE + 1)
#define        AF_E       (AF_BASE + 2)
#define        AF_LED     (AF_BASE + 3)

#define        AF_DB4     (AF_BASE + 4)
#define        AF_DB5     (AF_BASE + 5)
#define        AF_DB6     (AF_BASE + 6)
#define        AF_DB7     (AF_BASE + 7)

static int lcdHandle;

int main(void)
{   
    int i;
    int count;
	uchar tmp;
	float vol;
    
	if(wiringPiSetup() < 0){
		printf("wiringPi setup failed!\n");
		return -1;
	}

    pcf8574Setup(AF_BASE, 0x27); //pcf8574 I2C address
    
    lcdHandle = lcdInit (2,16,4,AF_RS,AF_E,AF_DB4,AF_DB5,AF_DB6,AF_DB7,0,0,0,0);
    
    if(lcdHandle < 0){
        fprintf(stderr, "lcdInit failed\n");
        exit(EXIT_FAILURE);
    }
    
    for(i=0;i<8;i++){
		pinMode(AF_BASE+i, OUTPUT);
	}

    digitalWrite(AF_LED, 1);
    digitalWrite(AF_RW,  0);
    
    printf("Raspberry Pi - Read voltage from ADC0832 and display on LCD1602\n");
	printf("...Working.........\n");
	printf("Press [Ctrl+C] to end\n");

    lcdHome(lcdHandle);
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, " www.adeept.com ");
    lcdPosition(lcdHandle, 0, 0);
    
	ADC0832_Init();
    
	while(1){
		tmp = get_ADC_Result();
		vol = 5.0/255 * tmp;
        
		lcdPosition(lcdHandle, 0, 0);
		lcdPrintf(lcdHandle, "Voltage: ");
        lcdPosition(lcdHandle, 9, 0);
        lcdPrintf(lcdHandle, "%2.2f V", vol);
        delay(100);
    }
    
    return 0;
}



