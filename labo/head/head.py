
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(23, GPIO.OUT)
p= GPIO.PWM(23,50)
p.start(8.5)

try:
	while True:
		p.ChangeDutyCycle(12.5) 
		time.sleep(1)
		print 'down'		
		p.ChangeDutyCycle(8.5) 
		time.sleep(1)
		print 'up'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
