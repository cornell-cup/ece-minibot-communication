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
            analoginput (:obj:`AnalogInput`): AnalogInput object for pin of sensor.
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
