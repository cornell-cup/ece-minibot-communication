"""
Tests for minibot movement.
"""
from minibot.bot import Bot

import json

CONFIG_LOCATION = '/home/pi/cs-minibot/minibot/configs/config.json'

if __name__ == "__main__":
    print("Initializing Minibot Software")
    config_file = open(CONFIG_LOCATION)
    config = json.loads(config_file.read())
    bot = Bot(config)
    color= bot.get_sensor_by_name("color")
    '''
    while true:
        print("Moving until BLUE")
        bot.move_forward(50)
        while color.get_color_name() != "BLUE":
           print("...")
           bot.wait(0.001)
        bot.stop()
        bot.wait(1)
        print("Turning off BLUE")
        bot.turn_clockwise(30)
        while color.get_color_name() == "BLUE":
           print("...")
           bot.wait(0.001)
        bot.stop()
        bot.wait(1)
    '''
    print(color.get_color_name())

