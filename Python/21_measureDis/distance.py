#! /usr/bin/python
import RPi.GPIO as GPIO
import time

Trig = 16
Echo = 18

def checkdist():
	GPIO.output(Trig, GPIO.HIGH)
	time.sleep(0.000015)
	GPIO.output(Trig, GPIO.LOW)
	while not GPIO.input(Echo):
		pass
	t1 = time.time()
	while GPIO.input(Echo):
		pass
	t2 = time.time()
	return (t2-t1)*340/2 * 100

def setup():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(Trig, GPIO.OUT, initial=GPIO.LOW)
	GPIO.setup(Echo, GPIO.IN)
	time.sleep(2)

