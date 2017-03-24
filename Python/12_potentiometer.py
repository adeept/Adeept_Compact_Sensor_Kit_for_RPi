#!/usr/bin/env python
import ADC0832
import time

def init():
	ADC0832.setup()

def loop():
	while True:
		res = ADC0832.getResult()
		vol = 5.0/255 * res
		print 'analog value: %03d  ||  voltage: %.2fV' %(res, vol)
		time.sleep(0.2)

if __name__ == '__main__':
	init()
	try:
		loop()
	except KeyboardInterrupt: 
		ADC0832.destroy()
		print 'The end !'
