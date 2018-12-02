//This program is for testing the chain lift on a 3-way switch (one up, one down, middle off)

// Initialize Variables

// Initializes Print Switches
int switchVal;
int lastSwitchVal;

// Initialization of Pins for Lift
int switchForward = 3;                    // pin for the lift up-switch position
int switchBack = 10;                      // pin for the lift down-switch position
int motorPin1 = 5;                        // pin for moving the motor up
int motorPin2 = 6;                        // pin for moving the motor down

void setup() {
  // Initialize pin types
  pinMode(switchForward,INPUT);           // sets the switchForward variable as an input
  pinMode(switchBack,INPUT);              // sets the switchBack variable as an input
  pinMode(motorPin1,OUTPUT);              // sets the motorPin1 variable as an output
  pinMode(motorPin2,OUTPUT);              // sets the motorPin2 variable as an output
  pinMode(switchPin, INPUT);              // sets the switchPin variable as an input

  // Allows Serial Outputs
  Serial.begin(9600);                     // allows printed statements and data on the monitor

  // Turns off LED
  pinMode(13,OUTPUT);
}

void loop() {
  // Code for Lift
  
  // If Statement for if the Down Switch is on
  if (digitalRead(switchBack) == HIGH) {
    switchVal = -1;
    delay(20);
    if (switchVal != lastSwitchVal) {
      Serial.println("DOWN");
      lastSwitchVal = -1;
    }
    analogWrite(motorPin1,190);           // if switchBack is on, motorPin1 is turned on as a PWM
    analogWrite(motorPin2,190);           // and motorPin2 is turned off
  }
  // If Statement for if the Up Switch is on
  if (digitalRead(switchForward) == HIGH) {
    switchVal = 1;
    delay(20);
    if (switchVal != lastSwitchVal) {
      Serial.println("UP");
      lastSwitchVal = 1;
    }
    analogWrite(motorPin1,50);           // if switchForward is on, motorPin2 is turned on as a PWM
    analogWrite(motorPin2,50);           // and motorPin1 is turned off
  }
  // If Statement for if Neither Switch is on
  if (digitalRead(switchBack) == LOW && digitalRead(switchForward) == LOW) {
    switchVal = 0;
    delay(20);
    if (switchVal != lastSwitchVal) {
      Serial.println("STABLE");
      lastSwitchVal = 0;
    }
    digitalWrite(motorPin1,HIGH);         // if neither is on, both motor pins are turned off
    digitalWrite(motorPin2,LOW);
  }
}
