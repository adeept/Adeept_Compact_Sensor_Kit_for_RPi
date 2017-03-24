#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
  
#define DATA_Pin 4  //DATA IN
#define CLK_Pin  5  //CLK IN
  
#define CmdMode  0x0000  // Work on 8-bit mode
#define ON       0x00ff       // 8-bit 1 data
#define SHUT     0x0000     // 8-bit 0 data
 
static int s_clk_flag = 0;
  
void send16bitData(unsigned int data)
{
    int i;
    for(i=0;i<16;i++)
    {
        if(data & 0x8000)
        {
            digitalWrite(DATA_Pin, HIGH);
        }
        else
        {
            digitalWrite(DATA_Pin, LOW);
        }
  
        if(s_clk_flag)
        {
            digitalWrite(CLK_Pin, LOW);
            s_clk_flag = 0;
        }
        else
        {
            digitalWrite(CLK_Pin, HIGH);
            s_clk_flag = 1;
        }
    	delayMicroseconds(20);
        data <<= 1;
    }
}
  
//latch routine for MY9221 data exchange
void latchData(void)
{
    int latch_flag = 0;
    int i;
    digitalWrite(DATA_Pin, LOW);
    delayMicroseconds(500);
    for(i=0;i<8;i++)
    { 
        if(latch_flag)
        {
            digitalWrite(DATA_Pin, LOW);
            latch_flag = 0;
        }
        else
        {
            digitalWrite(DATA_Pin, HIGH);
            latch_flag = 1;
        } 
    }
    delayMicroseconds(500);
} 
  
void sendLED(unsigned int LEDstate)
{
  unsigned char i;
  for(i=0;i<12;i++)
  {
    if(LEDstate&0x0001)
      send16bitData(ON);
    else
      send16bitData(SHUT);
    LEDstate=LEDstate>>1;
  }
}
  
int setup(void)
{
    printf("LED bar test code!\n");
    printf("Using DATA = GPIO4, CLK = GPIO5.\n");   
     
    if(wiringPiSetup()==-1)
    {
    printf("setup wiringPi failed ! \n");
    return 1;
    }
            
    pinMode(DATA_Pin,OUTPUT);   //Data pin
    pinMode(CLK_Pin,OUTPUT);    //CLK pin
    digitalWrite(DATA_Pin, LOW);
    digitalWrite(CLK_Pin, LOW);
    s_clk_flag = 0;
}

int setLedNum(int n)
{
	if(n<0 || n >10){
		printf("n = [0, 10]\n");
		return -1;
	}

    send16bitData(CmdMode);
    sendLED(pow(2,n)-1); // 2^n-1
    latchData();
}
  
int main(void)
{
	int i = 0;

	setup();

	while(1){
		for(i = 0; i < 11; i++){
	 		setLedNum(i);    	
			delay(1000);
		}
    }

	return 0;
}
