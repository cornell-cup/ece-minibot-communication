

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(38, GPIO.OUT)
p= GPIO.PWM(38,50)
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
