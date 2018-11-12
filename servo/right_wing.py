

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)


GPIO.setup(36, GPIO.OUT)
extend= GPIO.PWM(36,50)
extend.start(3.5)
#start with collapsed

GPIO.setup(32, GPIO.OUT)
flap= GPIO.PWM(32,50)
flap.start(6)
#start down
try:
	while True:
		flap.ChangeDutyCycle(6) 
		print 'flap up'		
		time.sleep(1)
		
		extend.ChangeDutyCycle(3.5) 
		print 'extend'		
		time.sleep(1)

		extend.ChangeDutyCycle(6.5)
		print 'collapse'
		time.sleep(1)

		flap.ChangeDutyCycle(4.0) 
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
