import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(16, GPIO.OUT)
p= GPIO.PWM(16,50)
p.start(3.50)


try:
	while True:
		p.ChangeDutyCycle(5.5) 
		time.sleep(1)
		print 'extend'		
		p.ChangeDutyCycle(3.5)
		time.sleep(1)
		print 'third'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
