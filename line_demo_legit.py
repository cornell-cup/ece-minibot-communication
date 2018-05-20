"""
Tests for minibot movement.
"""
from minibot.bot import Bot
from minibot.hardware.arduino.gpio import digitalRead
import time

import json

CONFIG_LOCATION = '/home/pi/cs-minibot/minibot/configs/config.json'

if __name__ == "__main__":
    print("Initializing Minibot Software")
    config_file = open(CONFIG_LOCATION)
    config = json.loads(config_file.read())
    bot = Bot(config)
    motor= bot.get_actuator_by_name("demo")
    motor.set_speed(50,50)
    print("Following line until intersection.")
    drive= 1
    lm = 3
    rm = 5
    spd = 225
    a = 80
    b = 160
    c = 225
    while drive:
        r3 = not digitalRead(11)
        r2 = not digitalRead(13)
        r1 = not digitalRead(14)
        l1 = not digitalRead(15)
        l2 = not digitalRead(16)
        l3 = not digitalRead(17)
        if l1+l2+l3+r1+r2+r3 >= 5:
            drive = 0
            bot.stop()
        else if (l1 && r1):
            bot.set_wheel_power(spd,spd)
        else if (l1):
            bot.set_wheel_power(spd-a,spd)
        else if (r1):
            bot.set_wheel_power(spd,spd-a)
        else if (l2):
            bot.set_wheel_power(spd-b,spd)
        else if (r2):
            bot.set_wheel_power(spd,spd-b)
        else if (l3):
            bot.set_wheel_power(spd-c,spd)
        else if (r3):
            bot.set_wheel_power(spd,spd-c)
        