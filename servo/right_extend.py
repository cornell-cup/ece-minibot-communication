import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(36, GPIO.OUT)
p= GPIO.PWM(36,50)
p.start(3.50)


try:
	while True:
		p.ChangeDutyCycle(6.5) 
		time.sleep(1)
		print 'extend'		
		p.ChangeDutyCycle(3.5)
		time.sleep(1)
		print 'third'
				
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
