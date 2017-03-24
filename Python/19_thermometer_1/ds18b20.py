#!/usr/bin/env python


def ds18b20Read():
	tfile = open("/sys/bus/w1/devices/28-0000062abd71/w1_slave")
	text = tfile.read()
	tfile.close()
	secondline = text.split("\n")[1]
	temperaturedata = secondline.split(" ")[9]
	temperature = float(temperaturedata[2:])
	temperature = temperature / 1000
	temperature = round(temperature, 2)
	print temperature
	return temperature
