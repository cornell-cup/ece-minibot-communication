import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(40, GPIO.OUT)
p= GPIO.PWM(40,50)
p.start(2.5)
#starts with extension
print 'extend'		
try:
	while True:
		#collapse
		p.ChangeDutyCycle(1.5) 
		time.sleep(1)
		print 'second'
		#extend		
		p.ChangeDutyCycle(2.5) 
		time.sleep(1)
		print 'third'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
