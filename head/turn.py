

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(5, GPIO.OUT)
p= GPIO.PWM(5,50)
p.start(7.5)

try:
	while True:
		p.ChangeDutyCycle(2.5) 
		time.sleep(1)
		print 'down'		
		p.ChangeDutyCycle(7.5) 
		time.sleep(1)
		print 'up'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
