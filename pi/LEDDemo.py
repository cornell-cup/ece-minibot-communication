import time
from ArduinoComm import *

while 1:
	digitalWrite(3,1)
	print("D4: "+str(digitalRead(4)))
	print("A0: "+str(analogRead(16)))
	x=0
	while x<=255:
		analogWrite(6,x)
		time.sleep(0.1)
		x+=10
	digitalWrite(3,0)
	time.sleep(0.5)

