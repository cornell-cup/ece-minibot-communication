

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(12, GPIO.OUT)
p= GPIO.PWM(12,50)
p.start(6)
#start down
try:
	while True:
		p.ChangeDutyCycle(4) 
		time.sleep(1)
		print 'up'		
		p.ChangeDutyCycle(6.0) 
		time.sleep(1)
		print 'down'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
