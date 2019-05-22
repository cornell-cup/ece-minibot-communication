

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)



GPIO.setup(21, GPIO.OUT)
lExtend= GPIO.PWM(21,50)
lExtend.start(5.5)
# left wing start with collapsed
GPIO.setup(20, GPIO.OUT)
lFlap= GPIO.PWM(20,50)
lFlap.start(3.5)
#left starts down

GPIO.setup(16, GPIO.OUT)
rExtend= GPIO.PWM(16,50)
rExtend.start(3.5)
#start with collapsed (right wing)

GPIO.setup(12, GPIO.OUT)
rFlap= GPIO.PWM(12,50)
rFlap.start(6)
#start down (right)
try:
	while True:
		lFlap.ChangeDutyCycle(6) 
		rFlap.ChangeDutyCycle(4) 
		print 'flap up'		
		time.sleep(1)
		
		lExtend.ChangeDutyCycle(3.5) 
		rExtend.ChangeDutyCycle(5.5) 
		print 'extend'		
		time.sleep(1)

		lExtend.ChangeDutyCycle(6.5)
		rExtend.ChangeDutyCycle(3.5) 	
		print 'collapse'
		time.sleep(1)

		lFlap.ChangeDutyCycle(4.0) 
		rFlap.ChangeDutyCycle(6.0) 
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
	rFlap.stop()
	rExtend.stop()
	lFlap.stop()
	lExtend.stop()
	GPIO.cleanup()

