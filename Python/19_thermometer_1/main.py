#!/usr/bin/env python

import RPi.GPIO as GPIO
import ds18b20
import segment
import time

def setup():
	segment.TM1638_init()

def destory():
	GPIO.cleanup()

def loop():
	tmp = 0.0
	while True:
		tmp = ds18b20.ds18b20Read()
		segment.numberDisplay_dec(tmp)
		time.sleep(0.1)

if __name__ == '__main__':
	setup()
	try:
		loop()
	except KeyboardInterrupt:
		destory()
