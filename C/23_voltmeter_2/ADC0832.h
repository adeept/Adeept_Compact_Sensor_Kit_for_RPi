#ifndef _ADC0832_H
#define _ADC0832_H

#include <wiringPi.h>
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

#define     ADC_CS    3
#define     ADC_DIO   4
#define     ADC_CLK   5

extern void ADC0832_Init(void);
extern uchar get_ADC_Result(void);

#endif
