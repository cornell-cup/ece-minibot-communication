
import sys
import time
import RPi.GPIO as GPIO 

#gpio ref
GPIO.setmode(GPIO.BCM)

#define GPIO signals to use
#using pins 37,35,33,31
#respectively GPIO pins: 26,19,13,6
#StepPins = [26,19,13,6]

#other stepper
#respectively GPIO pins: 17,18,21,22
#StepPins = [17,18,21,22]

#StepPins = [17,18,27,22]

StepPins = [8,11,9,10,17,18,27,22]



#setup pins
for pin in StepPins:
	print "Setup pins"
	GPIO.setup(pin,GPIO.OUT)
	GPIO.output(pin, 0)

Seq = [
	[1,0,0,0,1,0,0,1],
	[1,1,0,0,0,0,0,1],
	[0,1,0,0,0,0,1,1],
	[0,1,1,0,0,0,1,0],
	[0,0,1,0,0,1,1,0],
	[0,0,1,1,0,1,0,0],
	[0,0,0,1,1,1,0,0],
	[1,0,0,1,1,0,0,0]]
#for i in range(512):
for i in range(512):
  for step in reversed(range(8)):
    for pin in range(8):
	GPIO.output(StepPins[pin],Seq[step][pin])
    time.sleep(0.001)

time.sleep(2)

#for i in range(50):
 
    
for i in range(120): 
 for step in range(8):
    for pin in range(8):
	GPIO.output(StepPins[pin],Seq[step][pin])  
    time.sleep(0.001)
GPIO.cleanup()

