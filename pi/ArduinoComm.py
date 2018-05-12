import serial

ser = serial.Serial(

    port='/dev/serial0',
    baudrate = 1000000,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=5
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

def motorDrive(portPWM,portDig,pwm,dig):
    ser.write(b'M'+bytes([portPWM,portDig,pwm&255,dig&255]))

def hbridgeDrive(portPWM1,portDig1,pwm1,dig1,portPWM2,portDig2,pwm2,dig2):
    ser.write(b'H'+bytes([portPWM1,portDig1,pwm1&255,dig1&255,portPWM2,portDig2,pwm2&255,dig2&255]))

def sonar(portTrig,portEcho):
    ser.write(b'S'+bytes([portTrig,portEcho]))
    return int.from_bytes(ser.read(4),byteorder='big')
