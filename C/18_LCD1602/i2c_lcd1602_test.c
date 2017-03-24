#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>

#include <stdio.h>
#include <stdlib.h>

#define        AF_BASE    64
#define        AF_RS                (AF_BASE + 0)
#define        AF_RW                (AF_BASE + 1)
#define        AF_E                 (AF_BASE + 2)
#define        AF_LED               (AF_BASE + 3)

#define        AF_DB4               (AF_BASE + 4)
#define        AF_DB5               (AF_BASE + 5)
#define        AF_DB6               (AF_BASE + 6)
#define        AF_DB7               (AF_BASE + 7)

// Global lcd handle:
static int lcdHandle;

int main(void)
{   
    int i;
    int count;
    
	wiringPiSetup();

    pcf8574Setup(AF_BASE,0x3f); //pcf8574 I2C address
    
    lcdHandle = lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;
    
    if (lcdHandle < 0)
    {
        fprintf (stderr, "lcdInit failed\n") ;
        exit (EXIT_FAILURE) ;
    }
    
    for(i=0;i<8;i++)
          pinMode(AF_BASE+i,OUTPUT);
    digitalWrite(AF_LED,1);
    digitalWrite(AF_RW,0);
    
    printf ("Raspberry Pi - PCF8754 Test\n");
    lcdHome(lcdHandle);
    lcdClear(lcdHandle);
    lcdPosition (lcdHandle, 0, 0) ; 
    lcdPuts (lcdHandle, " www.adeept.com ") ;
    lcdPosition (lcdHandle, 0, 1) ; 
    
    FILE *fp;
    char temp_char[15];
    char Total[20];
    char Free[20];
    
    while(1)
    {   
        fp=fopen("/sys/class/thermal/thermal_zone0/temp","r");
        fgets(temp_char,9,fp);
        float Temp;
        Temp=atof(temp_char)/1000;
        lcdPosition (lcdHandle, 0, 1);
        lcdPrintf (lcdHandle, "%3.1fC", Temp) ; 
        fclose(fp);

        fp=fopen("/proc/meminfo","r");
        fgets(Total,19,fp);
        fgets(Total,4,fp);
        fgets(Free,9,fp);
        fgets(Free,19,fp);
        fgets(Free,4,fp);
        lcdPosition (lcdHandle, 7, 1);
        lcdPrintf (lcdHandle, "%3d/%3dMB", atoi(Free),atoi(Total)) ;
        fclose(fp);
        
        delay(1000);
    }
    
    return 0; 
}
