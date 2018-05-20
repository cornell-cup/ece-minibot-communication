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
    color = bot.get_sensor_by_name("color")
    print("Staying off the blue")
    while 1:
        if (color.get_color_name() == "BLUE"):
            bot.turn_clockwise(50)
            bot.wait(0.75)
        else:
            bot.move_forward(50)
