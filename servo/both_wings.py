

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(40, GPIO.OUT)
lExtend= GPIO.PWM(40,50)
lExtend.start(5.5)
# left wing start with collapsed
GPIO.setup(38, GPIO.OUT)
lFlap= GPIO.PWM(38,50)
lFlap.start(3.5)
#left starts down

GPIO.setup(36, GPIO.OUT)
rExtend= GPIO.PWM(36,50)
rExtend.start(3.5)
#start with collapsed (right wing)

GPIO.setup(32, GPIO.OUT)
rFlap= GPIO.PWM(32,50)
rFlap.start(6)
#start down (right)
try:
	while True:
		lFlap.ChangeDutyCycle(6) 
		rFlap.ChangeDutyCycle(5.5) 
		print 'flap up'		
		time.sleep(1)
		
		lExtend.ChangeDutyCycle(3.5) 
		rExtend.ChangeDutyCycle(2.5) 
		print 'extend'		
		time.sleep(1)

		lExtend.ChangeDutyCycle(6.5)
		rExtend.ChangeDutyCycle(5.5) 	
		print 'collapse'
		time.sleep(1)

		lFlap.ChangeDutyCycle(4.0) 
		rFlap.ChangeDutyCycle(3.5) 
		print 'flap down'
		time.sleep(1)


#		print 'flap up'		
#		time.sleep(1)
#		print 'extend'		
#		time.sleep(1)	
#		print 'collapse'
#		time.sleep(1)
#		print 'down'
#		time.sleep(1)
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()

