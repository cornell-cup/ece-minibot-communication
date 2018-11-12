

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(32, GPIO.OUT)
p= GPIO.PWM(32,50)
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
