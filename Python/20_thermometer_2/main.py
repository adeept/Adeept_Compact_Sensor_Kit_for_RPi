#!/usr/bin/env python

import RPi.GPIO as GPIO
import ds18b20
import i2c_lcd1602
import time

screen = i2c_lcd1602.Screen(bus=1, addr=0x27, cols=16, rows=2)

def destory():
   GPIO.cleanup()

def loop():
    while True:
       screen.cursorTo(0, 0)
       screen.println(line)
       t = ds18b20.ds18b20Read()
       t = round(t, 2)
       m = '%f' %t
       m = m[:5]
       screen.cursorTo(1, 0)
       screen.println(' Temp: ' + m + ' C  ')
       screen.clear()
       time.sleep(1)      

if __name__ == '__main__':
   print 'www.adeept.com'
   line = " www.adeept.com "
   screen.enable_backlight()
   screen.clear()
   try:
      loop()
   except KeyboardInterrupt:
      destory()
