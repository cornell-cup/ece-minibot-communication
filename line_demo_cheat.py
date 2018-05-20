"""
Tests for minibot movement.
"""
from minibot.bot import Bot
from minibot.hardware.arduino.gpio import start, stop
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
    start(150)
