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
    print("Following line until intersection.")
    drive= 1
    spd = 70
    a = 35
    b = 47
    c = 70
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
        elif (l1 and r1):
            bot.set_wheel_power(spd,spd)
        elif (l1):
            bot.set_wheel_power(spd-a,spd)
        elif (r1):
            bot.set_wheel_power(spd,spd-a)
        elif (l2):
            bot.set_wheel_power(spd-b,spd)
        elif (r2):
            bot.set_wheel_power(spd,spd-b)
        elif (l3):
            bot.set_wheel_power(spd-c,spd)
        elif (r3):
            bot.set_wheel_power(spd,spd-c)
        