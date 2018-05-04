unsigned char vars[10];
unsigned int x;

void setup() {
  Serial.begin(1000000);
}

void loop() {
  
}

void serialEvent() {
  while (Serial.available()) {
    unsigned char command= Serial.read();
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
    }
  }
}

