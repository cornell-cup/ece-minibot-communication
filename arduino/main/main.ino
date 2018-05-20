unsigned char vars[10];
unsigned int x;


unsigned char drive;
unsigned char lm= 3;
unsigned char rm= 5;
unsigned char spd= 150;
unsigned char a= 5;
unsigned char b= 15;
unsigned char c= 30;

void setup() {
  Serial.begin(1000000);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {

  if (drive) {
    char r3= digitalRead(11);
    char r2= digitalRead(13);
    char r1= digitalRead(A0);
    char l1= digitalRead(A1);
    char l2= digitalRead(A2);
    char l3= digitalRead(A3);
    if (l1 && l2 && l3 && r1 && r1 && r3) {
      drive= 0;
    } else if (l1 && r1) {
      analogWrite(rm,spd);
      analogWrite(lm,spd);
    } else if (l1) {
      analogWrite(rm,spd-a);
      analogWrite(lm,spd+a);
    } else if (r1) {
      analogWrite(rm,spd+a);
      analogWrite(lm,spd-a);
    } else if (l2) {
      analogWrite(rm,spd-b);
      analogWrite(lm,spd+b);
    } else if (r2) {
      analogWrite(rm,spd+b);
      analogWrite(lm,spd-b);
    } else if (l3) {
      analogWrite(rm,spd-c);
      analogWrite(lm,spd+c);
    } else if (r3) {
      analogWrite(rm,spd+c);
      analogWrite(lm,spd-c);
    }
  }
  
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
      case 'Z' : //turn drive on
        Serial.readBytes(vars, 1);
        spd= vars[0];
        if (spd > 225) spd = 225;
        else if (spd < 30) spd = 30;
        drive= 1;
        break;
      case 'X' : //turn drive off
        drive= 0;
        break;
    }
  }
}

