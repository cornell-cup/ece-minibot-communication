

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(20, GPIO.OUT)
p= GPIO.PWM(20,50)
p.start(3.5)

try:
	while True:
		p.ChangeDutyCycle(5.5) 
		time.sleep(1)
		print 'down'		
		p.ChangeDutyCycle(3.5) 
		time.sleep(1)
		print 'up'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
