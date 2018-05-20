# ece-minibot-communication

Code for UART communication between the Pi and Arduino

## Use

A few things must first be configured on the Pi.
1. Clone this repository
2. Link this repository to directory cs-minibot using command "ln -s ~/ece-minibot-communication ~/cs-minibot"
3. Enable UART in system options
4. Remove line "console=serial0,115200" from /boot/cmdline.txt

The Arduino does not require special configuration, simply program it with arduino/main/main.ino

## Performance

Performance had been characterized using a [Python script](https://github.com/cornell-cup/ece-minibot-communication/blob/master/pi/SpeedTest.py) which times 10,000 performances of each GPIO command. The results using a baud rate of 1MHz are as follows:

| Command      | Total time (s) | Time per command (ms) |
| ------------ | -------------- | --------------------- |
| digitalWrite |          3.528 |	                0.353 |
| analogWrite  |	        3.558	|                 0.356 |
| digitalRead  |        	9.604	|                 0.960 |
| analogRead   |         	9.991	|                 0.999 |
| motorDrive   |          3.786 |                 0.379 |

Write commands require an average of ~0.4 ms, while read commands require an average of ~1 ms. The best apparent potential action to improve performance is finding better serial libraries for either of the Pi or Arduino.
