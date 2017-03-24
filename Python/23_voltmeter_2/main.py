#!/usr/bin/env python

import RPi.GPIO as GPIO
import ADC0832
import i2c_lcd1602
import time

screen = i2c_lcd1602.Screen(bus=1, addr=0x27, cols=16, rows=2)

def destory():
	GPIO.cleanup()

def loop():
	while True:
		screen.cursorTo(0, 0)
		screen.println(line)
		t = ADC0832.getResult()
		vol = 5.0/255 * t
		vol = round(vol, 2)
		vol = '%f' %vol
		vol = vol[:4]
		screen.cursorTo(1, 0)
		screen.println(' Voltage: ' + vol + 'V ')
		screen.clear()
		time.sleep(0.2)      

if __name__ == '__main__':
	print 'www.adeept.com'
	line = " www.adeept.com "
	screen.enable_backlight()
	screen.clear()
	try:
		ADC0832.setup()
		loop()
	except KeyboardInterrupt:
		destory()
