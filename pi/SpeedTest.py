import timeit

n=1000
for command in ['digitalWrite(3,1)','analogWrite(6,200)','digitalRead(4)','analogRead(16)','motorDrive(3,6,120,0)','hbridgeDrive(3,6,120,0,5,8,120,0)']:
	x= timeit.timeit('ArduinoComm.'+command, setup= 'import ArduinoComm', number=n)
	print(command+"\n    Total time elapse: "+str(x)+"\n    Time per command: "+str(x/n))
