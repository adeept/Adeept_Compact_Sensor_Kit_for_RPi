#include "segment.h"

static void _shiftOut(unsigned char dataPin, unsigned char clockPin, unsigned char bitOrder, unsigned char val)
{
      unsigned char i;

      for (i = 0; i < 8; i++)
      {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));
        digitalWrite(clockPin, HIGH);
		delayMicroseconds(1);
        digitalWrite(clockPin, LOW);
		delayMicroseconds(1);
      }
}

static void sendCommand(unsigned char value) 
{ 
	digitalWrite(stbPin, LOW);
	_shiftOut(dioPin, clkPin, LSBFIRST, value);
	digitalWrite(stbPin, HIGH);
}  

extern void TM1638_init(void) 
{ 
	pinMode(stbPin, OUTPUT);
	pinMode(clkPin, OUTPUT);
	pinMode(dioPin, OUTPUT);
	sendCommand(0x8f);       //activate 
} 

extern void numberDisplay(unsigned int num) //num must be 0~9999 
{  /*0*/ /*1*/ /*2*/ /*3*/ /*4*/ /*5*/ /*6*/ /*7*/ /*8*/ /*9*/ 
	unsigned char digits[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	
	sendCommand(0x40);
	digitalWrite(stbPin, LOW);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0xc0);
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[num/1000%10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00);   
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[num/100%10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00); 
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[num/10%10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00); 
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[num%10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00);
	digitalWrite(stbPin, HIGH);
}

extern void numberDisplay_dec(float num) // 00.00~99.99
{  /*0*/ /*1*/ /*2*/ /*3*/ /*4*/ /*5*/ /*6*/ /*7*/ /*8*/ /*9*/ 
	unsigned char digits[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

	unsigned int integer = 0;
	unsigned int decimal = 0;
	
	unsigned int pro = num * 100;

	integer = pro / 100;
	decimal = pro % 100;

	sendCommand(0x40);
	digitalWrite(stbPin, LOW);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0xc0);
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[integer/10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00);   
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[integer%10] | 0x80);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00); 
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[decimal/10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00); 
	_shiftOut(dioPin, clkPin, LSBFIRST, digits[decimal%10]);
	_shiftOut(dioPin, clkPin, LSBFIRST, 0x00);
	digitalWrite(stbPin, HIGH);
}
