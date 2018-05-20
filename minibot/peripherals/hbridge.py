"""
Minibot H-Bridge.
"""

class HBridge():
    """
    Minibot H-Bridge class.
    """
    def __init__(self, hbridge):
        """
        Constructor.
        Args:
            hbridge (:obj:`HBridgeOut`): HBridge output object.
        """
        self.hbridge= hbridge

        self.left_speed = 0
        self.right_speed = 0

    def get_speed(self):
        """
        Returns the (left speed, right speed) tuple
        """
        return (self.left_speed, self.right_speed)
        
    def set_speed(self, left, right):
        """
        Sets the speed of both motors.
        Args:
            left (float): The speed of the left motor (-100 to 100).
            right (float): The speed of the right motor (-100 to 100).
        """
        self.left_speed = max(min(left, 100.0), -100.0)
        self.right_speed = -max(min(right, 100.0), -100.0)
        # divide by hundred because PWMs have values between 1 and -1
        # values are negated because of the wiring setup
        left = self.left_speed/100.0
        right = self.right_speed/100.0

        right_pwm = abs(right)
        left_pwm = abs(left)

        if left < 0:
            left_dig = 1
        else:
            left_dig = 0

        if right < 0:
            right_dig = 1
        else:
            right_dig = 0

        self.hbridge.drive(left_pwm,left_dig,right_pwm,right_dig)

