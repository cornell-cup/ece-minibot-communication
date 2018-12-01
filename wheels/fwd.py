
import RPi.GPIO as GPIO
import time
import sys
GPIO.setmode(GPIO.BOARD)

GPIO.setup(7, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)

try:
  while True:
 	GPIO.output(7,GPIO.HIGH)
  	GPIO.output(18,GPIO.LOW)
except KeyboardInterrupt:
    GPIO.output(7,GPIO.LOW)
    print ('interrupt')
    GPIO.cleanup()
    sys.exit(0)
