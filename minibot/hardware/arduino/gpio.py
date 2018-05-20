"""
Minibot GPIO, to control Arduino GPIO over UART.
"""

from minibot.hardware.gpio import PWM as MPWM
from minibot.hardware.gpio import DigitalInput as MDigitalInput
from minibot.hardware.gpio import DigitalOutput as MDigitalOutput
from math import floor as floor
import serial

ser = serial.Serial(

    port='/dev/serial0',
    baudrate = 1000000,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=2
)

def input(port):
    ser.write(b'I'+bytes([port]))

def output(port):
    ser.write(b'O'+bytes([port]))

def digitalWrite(port,val):
    ser.write(b'E'+bytes([port,val&255]))

def digitalRead(port):
    ser.write(b'D'+bytes([port]))
    return int.from_bytes(ser.read(1),byteorder='big')

def analogWrite(port,val):
    ser.write(b'B'+bytes([port,val&255]))

def analogRead(port):
    ser.write(b'A'+bytes([port]))
    return int.from_bytes(ser.read(2),byteorder='big')

def motorDrive(portPWM,portDig,PWM,dig):
    ser.write(b'M'+bytes([portPWM,portDig,PWM&255,dig&255]))

def hbridgeDrive(portPWM1,portDig1,PWM1,dig1,portPWM2,portDig2,PWM2,dig2):
    ser.write(b'H'+bytes([portPWM1,portDig1,PWM1&255,dig1&255,portPWM2,portDig2,PWM2&255,dig2&255]))

def sonar(portTrig,portEcho):
    ser.write(b'S'+bytes([portTrig,portEcho]))
    return int.from_bytes(ser.read(4),byteorder='big')

def color():
    ser.write(b'C')
    x= ser.read(6)
    return int.from_bytes(x[0:2],byteorder='big'),
            int.from_bytes(x[2:4],byteorder='big'),
            int.from_bytes(x[4:6],byteorder='big')


class DigitalInput(MDigitalInput):
    """
    Digital input pin.
    """
    def __init__(self, pin):
        """
        Constructor.
        Args:
            pin (int): Digital pin number.
        """
        MDigitalInput.__init__(self, pin)
        input(pin)

    def read(self):
        """
        Read digital input from the pin.
        Return:
            int: 0 or 1 for LOW or HIGH voltage.
        """
        return digitalRead(self.pin)

class DigitalOutput(MDigitalOutput):
    """
    Digital output pin.
    """
    def __init__(self, pin):
        """
        Constructor.
        Args:
            pin (int): Digital pin number.
        """
        MDigitalOutput.__init__(self, pin)
        output(pin)

    def set_low(self):
        """
        Set the digital output pin to low.
        """
        digitalWrite(self.pin, 0)

    def set_high(self):
        """
        Set the digital output pin to high.
        """
        digitalWrite(self.pin, 1)

class PWM(MPWM):
    """
    PWM used on a minibot.
    """
    def __init__(self, pin, frequency=1, duty_cycle=0):
        """
        Constructor.
        Args:
            pin (int): Pin that the PWM is connected to on the Arduino.
            frequency (int): Frequency of the PWM.
            duty_cycle (int): Duty cycle of the PWM.
        """
        MPWM.__init__(self, pin, frequency, duty_cycle)
        output(pin)
        analogWrite(pin,floor(duty_cycle*255))

    def set_frequency(self, frequency):
        """
        Sets frequency of the PWM on the minibot.
        Args:
            frequency (int): New frequency on the minibot.
        """
        MPWM.set_frequency(self, frequency)
        raise NotImplementedError("PWM.set_frequency: cannot set PWM frequency on Arduino")

    def set_duty_cycle(self, duty_cycle):
        """
        Sets duty cycle of the PWM on the minibot.
        Args:
            duty_cycle (int): New duty cycle for the PWM.
        """
        MPWM.set_duty_cycle(self, duty_cycle)
        analogWrite(self.pin,floor(duty_cycle*255))

    def stop(self):
        """
        Stops the PWM on the minibot.
        """
        MPWM.stop(self)
        analogWrite(self.pin,0)

class AnalogInput:
    """
    Analog input pin.
    """
    def __init__(self, pin):
        """
        Constructor.
        Args:
            pin (int): Analog pin number.
        """
        self.pin = pin
        input(pin)

    def read(self):
        """
        Read analog input from the pin.
        Return:
            int: value between 0 and 1023
        """
        return analogRead(self.pin)

class MotorOut:
    """
    Motor countrol output pins
    """
    def __init__(self,pinPWM,pinDigital):
        """
        Constructor.
        Args:
            pinPWM (int): PWM pin number.
            pinDigital (int): Digital pin number.
        """
        self.pinPWM = pinPWM
        self.pinDigital = pinDigital
        output(pinPWM)
        output(pinDigital)
        self.stop()

    def drive(self,PWM_duty_cycle,digital_state):
        """
        Drive motor by setting PWM pin's duty cycle and Digital pin's state
        Args:
            PWM_duty_cycle (float): New duty cycle of PWM pin
            digital_state (int): Digital pin's state (0=LOW, 1=HIGH)
        """
        motorDrive(self.pinPWM, self.pinDigital, floor(PWM_duty_cycle*255), digital_state)

    def stop(self):
        motorDrive(self.pinPWM, self.pinDigital, 0, 1)

class HBridgeOut:
    """
    HBridge countrol output pins
    """
    def __init__(self,left_pin_PWM,left_pin_digital,right_pin_PWM,right_pin_digital):
        """
        Constructor.
        Args:
            left_pin_PWM (int): PWM pin number for left side.
            left_pin_digital (int): Digital pin number for left side.
            right_pin_PWM (int): PWM pin number for right side.
            right_pin_digital (int): Digital pin number for right side.
        """
        self.left_pin_PWM = left_pin_PWM
        self.left_pin_digital = left_pin_digital
        self.right_pin_PWM = right_pin_PWM
        self.right_pin_digital = right_pin_digital
        output(left_pin_PWM)
        output(left_pin_digital)
        output(right_pin_PWM)
        output(right_pin_digital)
        self.stop()

    def drive(self,left_PWM_duty_cycle,left_digital_state,right_PWM_duty_cycle,right_digital_state):
        """
        Drive HBridge by setting PWM pin's duty cycle and Digital pin's state
        Args:
            left_PWM_duty_cycle (float): New duty cycle of PWM pin on left side
            left_digital_state (int): Digital pin's state on left side (0=LOW, 1=HIGH)
            right_PWM_duty_cycle (float): New duty cycle of PWM pin on right side
            right_digital_state (int): Digital pin's state on right side (0=LOW, 1=HIGH)
        """
        hbridgeDrive(self.left_pin_PWM, self.left_pin_digital, floor(left_PWM_duty_cycle*255), left_digital_state,
            self.right_pin_PWM, self.right_pin_digital, floor(right_PWM_duty_cycle*255), right_digital_state)

    def stop(self):
        """
        Stop HBridge
        """
        hbridgeDrive(self.left_pin_PWM, self.left_pin_digital, 0, 1,
            self.right_pin_PWM, self.right_pin_digital, 0, 1)



class SonarSensor:
    """
    Sonar sensor read device
    """
    def __init__(self, pinTrig, pinEcho):
        """
        Constructor.
        Args:
            pinTrig (int): trig pin number.
            pinEcho (int): echo pin number.
        """
        self.pinTrig = pinTrig
        self.pinEcho = pinEcho
        input(pinTrig)
        input(pinEcho)

    def read(self):
        """
        Read distance from somar sensor
        Return:
            float: distance read by sonar sensor in cm
        """
        return sonar(self.pinTrig,self.pinEcho)*0.0343/2 #distance= (round trip duration/2)*speed of sound

class ColorSensor:
    """
    Color sensor read device
    """
    def __init__(self):
        """
        Constructor.
        Args:

        """

    def get_raw_data(self):
        """
        Read distance from somar sensor
        Return:
            [R,G,B]: red green and blue values from color sensor
        """
        return color()

