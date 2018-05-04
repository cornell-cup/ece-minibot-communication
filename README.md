# ece-minibot-communication

Code for UART communication between the Pi and Arduino

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

Increasing the baud rate further is not a good method of improving performance. The current baud rate of 1MHz was established through a series of tests in which 10,000 of each command were sent from the Pi to the Arduino as rapidly as possible and the total number of commands performed tracked by the Arduino. If the numbers of commands sent by the Pi and performed by the Arduino match, we can reasonably expect that both devices are capable of performing at that rate. We tested, in order, 115.2kHz, 1MHz, and 2MHz. The test failed at 2MHz. In order to verify that 1MHz will work consistently, the test was successfully repeated at 1MHz with 100,000 commands. 
