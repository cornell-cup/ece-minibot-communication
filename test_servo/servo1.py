import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(12,GPIO.OUT)
p = GPIO.PWM(12,50)
p.start(3.5)

try:
	while True:
		p.ChangeDutyCycle(6)
		time.sleep(1)
		
		p.ChangeDutyCycle(3.5)
		time.sleep(1)
except KeyboardInterrupt:
	p.stop()
	GPIO.cleanup()
