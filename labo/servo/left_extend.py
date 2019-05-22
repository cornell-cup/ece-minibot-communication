import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(21, GPIO.OUT)
p= GPIO.PWM(21,50)
p.start(5.5)
#starts with extension
print 'extend'		
try:
	while True:
		#collapse
		p.ChangeDutyCycle(3.5) 
		time.sleep(1)
		print 'second'
		#extend		
		p.ChangeDutyCycle(5.5) 
		time.sleep(1)
		print 'third'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
