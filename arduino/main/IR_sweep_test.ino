//Set up servo
#include <Servo.h>
Servo myservo;
int pos = 90;


// constants won't change. They're used here to set pin numbers:
const int PinA = 5;     // the number of the pushbutton pin
const int PinB = 6;
const int maxAngleA = 180;
const int minAngleB = 0;
const int del = 15;

// variables will change:
int switchState = 0;  // variable for reading the pushbutton status
int lastSwitchState;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);

  myservo.attach(9);
  myservo.write(pos);
}

void loop() {
  int switchA = digitalRead(PinA);
  int switchB = digitalRead(PinB);
  while(switchA == HIGH && pos <= maxAngleA){
    pos = pos + 1;
    myservo.write(pos);
    delay(del);
    switchA = digitalRead(PinA);
    switchB = digitalRead(PinB);
  }
  while(switchB == HIGH && pos >= minAngleB){
    pos = pos - 1;
    myservo.write(pos);
    delay(del);
    switchA = digitalRead(PinA);
    switchB = digitalRead(PinB);
  }
}

