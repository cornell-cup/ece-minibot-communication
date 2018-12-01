

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)


GPIO.setup(16, GPIO.OUT)
extend= GPIO.PWM(16,50)
extend.start(3.5)
#start with collapsed

GPIO.setup(12, GPIO.OUT)
flap= GPIO.PWM(12,50)
flap.start(6)
#start down
try:
	while True:
		flap.ChangeDutyCycle(4) 
		print 'flap up'		
		time.sleep(1)
		
		extend.ChangeDutyCycle(5.5) 
		print 'extend'		
		time.sleep(1)

		extend.ChangeDutyCycle(3.5)
		print 'collapse'
		time.sleep(1)

		flap.ChangeDutyCycle(6.0) 
		print 'flap down'
		time.sleep(1)


#try:
#	while True:
#		flap.ChangeDutyCycle(5.5) 
#		print 'flap up'		
#		time.sleep(1)
#		extend.ChangeDutyCycle(2.5) 
#		print 'extend'		
#		time.sleep(1)	
#		extend.ChangeDutyCycle(5.5) 	
#		print 'collapse'
#		time.sleep(1)
#		flap.ChangeDutyCycle(3.5) 
#		print 'down'
#		time.sleep(1)
				
except KeyboardInterrupt:
	flap.stop()
	extend.stop()
	GPIO.cleanup()
