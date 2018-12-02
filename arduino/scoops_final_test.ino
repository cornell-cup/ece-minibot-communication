//Set up servo
#include <Servo.h>
Servo myservo;
int pos = 0;


// constants won't change. They're used here to set pin numbers:
const int switchPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int switchState = 0;  // variable for reading the pushbutton status
int lastSwitchState;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(switchPin, INPUT);

  myservo.attach(9);
  myservo.write(pos);
}

void loop() {
  switchState = digitalRead(switchPin);
  if(switchState != lastSwitchState){
    if (switchState == HIGH){
      for (pos = 0; pos <= 50; pos += 1){
        myservo.write(pos);
        delay(15);
      }
    } else {
        for (pos = 50; pos >= 0; pos -= 1){
          myservo.write(pos);
          delay(15);
        }
      }
      delay(50);
  }
  lastSwitchState = switchState;
}


