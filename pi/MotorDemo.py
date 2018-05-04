import time
import Motor

moto = Motor.Motor(3,6)
while 1:
	for i in range(0,255,10):
		moto.CCW(i)
		time.sleep(0.1)
	moto.stop()
	time.sleep(1)
	for i in range(0,255,10):
		moto.CW(i)
		time.sleep(0.1)
	moto.stop()
	time.sleep(1)

