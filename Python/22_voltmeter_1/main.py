#!/usr/bin/env python

import RPi.GPIO as GPIO
import ADC0832
import segment
import time

def destory():
	GPIO.cleanup()

def setup():
	segment.TM1638_init()
	ADC0832.setup()

def loop():
	while True:
		t = ADC0832.getResult()
		vol = 5.0/255 * t
		vol = round(vol, 2)
		segment.numberDisplay_dec(vol)
		time.sleep(0.1)      

if __name__ == '__main__':
	print 'www.adeept.com'
	setup()
	try:
		loop()
	except KeyboardInterrupt:
		destory()
