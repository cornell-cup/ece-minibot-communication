from minibot.hardware.arduino.gpio import AnalogInput

"""
Minibot Analog Sensor.
"""

class AnalogSensor():
    """
    Minibot miscellaneous analog sensor class
    For use with line sensors and whatever else you could want
    """
    def __init__(self, name, pin_number):
        """
        Constructor.
        Args:
            pin_number (int): pin number on arduino of input pin
        """
        self.name = name
        self.analoginput = AnalogInput(pin_number)

    def read(self):
        """
        Returns the reading of sensor, float ranging from 0 to 1
        """
        return self.analoginput.read()/255.0

    def get_name(self):
        """
        Gets name of sensor.
        """
        return self.name
