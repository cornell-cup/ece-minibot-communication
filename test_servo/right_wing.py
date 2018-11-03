import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(40, GPIO.OUT)
p= GPIO.PWM(40,50)
p.start(2)

try:
	while True:
		p.ChangeDutyCycle(5.5) 
		time.sleep(1)
		print 'second'		
		p.ChangeDutyCycle(3.5) 
		time.sleep(1)
		print 'third'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
