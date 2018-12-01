import sys
import time
import RPi.GPIO as GPIO 

#gpio ref
GPIO.setmode(GPIO.BCM)

#define GPIO signals to use
#using pins 11,12,13,15
#respectively GPIO pins: 17,18,21,22
#StepPins = [17,18,21,22]

StepPins = [17,18,27,22]

#setup pins
for pin in StepPins:
	print "Setup pins"
	GPIO.setup(pin,GPIO.OUT)
	GPIO.output(pin, 0)

# Define sequence (given by manufacturer)
Seq = [
#[1,0,0,1],
	[1,0,0,0],
	[1,1,0,0],
	[0,1,0,0],
	[0,1,1,0],
	[0,0,1,0],
	[0,0,1,1],
	[0,0,0,1],
	[1,0,0,1]]
StepCount = len(Seq)
StepDir = 1 #clockwise (max is 2)

#command line
if len(sys.argv)>1:
   WaitTime = int(sys.argv[1])/float(1000)
else:
   WaitTime = 4/float(1000)

 # Initialize variables
StepCounter = 0

while True:

	print StepCounter,
	print Seq[StepCounter]
 	
	for pin in range(0,4):
	  xpin = StepPins[pin]
          if Seq[StepCounter][pin] != 0:
	   print " Enable GPIO %i" %(xpin)
	   GPIO.output(xpin, True)
	  else:
	    GPIO.output(xpin, False)
	StepCounter += StepDir

#restart if end of sequence
	if (StepCounter >= StepCount):
	  StepCounter = 0
	if (StepCounter<0):
	  StepCounter = StepCount + StepDir
	time.sleep(WaitTime)

