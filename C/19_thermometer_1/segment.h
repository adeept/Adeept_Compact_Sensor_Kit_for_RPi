#ifndef _segment_H
#define _segment_H

#include <wiringPi.h>

#define stbPin  0
#define clkPin  1
#define dioPin  2

#define LSBFIRST 0
#define MSBFIRST 1

static void _shiftOut(unsigned char dataPin, unsigned char clockPin, unsigned char bitOrder, unsigned char val);
static void sendCommand(unsigned char value);
extern void TM1638_init(void);
extern void numberDisplay(unsigned int num); //num must be 0~9999 
extern void numberDisplay_dec(float num); // 00.00~99.99

#endif
