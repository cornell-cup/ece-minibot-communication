from minibot.hardware.arduino.gpio import SonarSensor as Sonar

"""
Minibot Sonar Sensor.
"""

class SonarSensor():
    """
    Minibot sonar sensor class
    For use with HC-SR04 sonar sensor
    """
    def __init__(self, name, pin_number_Trig, pin_number_Echo):
        """
        Constructor.
        Args:
            pin_number_Trig (int): pin number on arduino of Trig pin
            pin_number_Echo (int): pin number on arduino of Echo pin
        """
        self.name = name
        self.sonar = Sonar(pin_number_Trig, pin_number_Echo)

    def read(self):
        """
        Returns distance measured by sensor in cm
        """
        return self.sonar.read()

    def get_name(self):
        """
        Gets name of sensor.
        """
        return self.name
