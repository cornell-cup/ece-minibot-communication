

import RPi.GPIO as GPIO
import time
import sys
GPIO.setmode(GPIO.BCM)

GPIO.setup(30, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)
while True:
  GPIO.output(30,0)
  GPIO.output(26,1)
GPIO.cleanup()
