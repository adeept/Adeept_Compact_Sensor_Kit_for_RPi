#ifndef _DIS_H
#define _DIS_H

#include <wiringPi.h>  
#include <stdio.h>  
#include <sys/time.h>  

#define  Trig    4  
#define  Echo    5  

extern void ultraInit(void); 

extern float get_distance(void);  

#endif
