from ArduinoComm import motorDrive
from ArduinoComm import output

class Motor:
	def __init__(self,pinPWM,pinDigital):
		self.pinPWM = pinPWM
		self.pinDigital = pinDigital
		output(pinPWM)
		output(pinDigital)

	def CW(self,pwm):
		motorDrive(self.pinPWM, self.pinDigital, 255-pwm, 0)

	def CCW(self,pwm):
		motorDrive(self.pinPWM, self.pinDigital, pwm, 1)

	def stop(self):
		motorDrive(self.pinPWM, self.pinDigital, 0, 1)
