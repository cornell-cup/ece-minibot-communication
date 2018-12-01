

import RPi.GPIO as GPIO
import time
import sys
GPIO.setmode(GPIO.BCM)

GPIO.setup(4, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)

try:
  while True:
  	GPIO.output(4,GPIO.LOW)
  	GPIO.output(24,GPIO.LOW)
except KeyboardInterrupt:
    GPIO.output(4,GPIO.LOW)
    print ('interrupt')
    GPIO.cleanup()
    sys.exit(0)
