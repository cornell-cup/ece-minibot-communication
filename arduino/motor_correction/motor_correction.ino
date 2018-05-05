//For serial communication
unsigned char vars[10];
unsigned int x;

//For feedback motor control
unsigned char motor1;
unsigned char motor2;
unsigned char motor1val;
unsigned char motor2val;
unsigned char motor1monitor = 0;
unsigned char motor2monitor = 0;
int motorcount;
#define motor1monitorpin 12
#define motor2monitorpin 10

void setup() {
  Serial.begin(1000000);


  pinMode(motor1monitorpin, INPUT);
  pinMode(motor2monitorpin, INPUT);
}

void loop() {
  motorcount = 0;
  for (unsigned int i = 0; i < 20000; i++) {
    if (!motor1monitor && digitalRead(motor1monitorpin)) {
      motor1monitor = 1;
      ++motorcount;
    } else if (motor1monitor && !digitalRead(motor1monitorpin)) {
      motor1monitor = 0;
    }
    if (!motor2monitor && digitalRead(motor2monitorpin)) {
      motor2monitor = 1;
      --motorcount;
    } else if (motor2monitor && !digitalRead(motor2monitorpin)) {
      motor2monitor = 0;
    }
  }
  if (motorcount > 0) {
    motor1val += 1;
    motor2val -= 1;
  } else if (motorcount < 0) {
    motor1val -= 1;
    motor2val += 1;
  }
  analogWrite(motor1, motor1val);
  analogWrite(motor2, motor2val);
}

void serialEvent() {
  while (Serial.available()) {
    unsigned char command = Serial.read();
    switch (command) {
      case 'D' : //digital read
        Serial.readBytes(vars, 1);
        Serial.write(digitalRead(vars[0]));
        break;
      case 'A' : //analog read
        Serial.readBytes(vars, 1);
        x = analogRead(vars[0]);
        Serial.write((x >> 8) & 0xFF);
        Serial.write(x & 0xFF);
        break;
      case 'E' : //digital write
        Serial.readBytes(vars, 2);
        digitalWrite(vars[0], vars[1]);
        break;
      case 'B' : //analog write
        Serial.readBytes(vars, 2);
        analogWrite(vars[0], vars[1]);
        break;
      case 'M' : //motor drive
        Serial.readBytes(vars, 4);
        digitalWrite(vars[1], vars[3]);
        analogWrite(vars[0], vars[2]);
        break;
      case 'H' : //H bridge drive
        Serial.readBytes(vars, 8);
        motor1val = vars[2];
        motor2val = vars[6];
        motor1 = vars[0];
        motor2 = vars[4];
        digitalWrite(vars[1], vars[3]);
        analogWrite(vars[0], vars[2]);
        digitalWrite(vars[5], vars[7]);
        analogWrite(vars[4], vars[6]);
        break;
      case 'O' : //declare output pin
        Serial.readBytes(vars, 1);
        pinMode(vars[0], OUTPUT);
        break;
      case 'I' : //declare input pin
        Serial.readBytes(vars, 1);
        pinMode(vars[0], INPUT);
        break;
    }
  }
}

