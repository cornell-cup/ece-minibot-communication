
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(21, GPIO.OUT)
extend= GPIO.PWM(21,50)
extend.start(5.5)
#start with collapsed
GPIO.setup(20, GPIO.OUT)
flap= GPIO.PWM(20,50)
flap.start(3.5)
#starts down
try:
	while True:
		flap.ChangeDutyCycle(5.5) 
		print 'flap up'		
		time.sleep(1)
		extend.ChangeDutyCycle(2.5) 
		print 'extend'		
		time.sleep(1)	
		extend.ChangeDutyCycle(5.5) 	
		print 'collapse'
		time.sleep(1)
		flap.ChangeDutyCycle(3.5) 
		print 'down'
		time.sleep(1)
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()



