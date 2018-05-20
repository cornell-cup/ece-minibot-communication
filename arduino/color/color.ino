//#include <Wire.h>
//#include "Adafruit_TCS34725.h"

///VARIABLES FOR COMMUNICATION PROTOCOL
unsigned char vars[10];
unsigned long x;

///VARIABLES FOR RGB
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c;


void setup() {
  Serial.begin(1000000);
  //tcs.begin();
}

void loop() {

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
      case 'S' : //Sonar sensor - return time diff in microseconds
        Serial.readBytes(vars, 2);
        digitalWrite(vars[0], LOW);
        delayMicroseconds(2);
        digitalWrite(vars[0], HIGH);
        delayMicroseconds(10);
        digitalWrite(vars[0], LOW);
        x = pulseIn(vars[1], HIGH);
        Serial.write((x >> 24) & 0xFF);
        Serial.write((x >> 16) & 0xFF);
        Serial.write((x >> 8) & 0xFF);
        Serial.write(x & 0xFF);
        break;
      case 'C' : //Color sensor - return R,G,B
        //tcs.getRawData(&r, &g, &b, &c);
        r=g=b=65000;
        Serial.write((r >> 8) & 0xFF);
        Serial.write(r & 0xFF);
        Serial.write((g >> 8) & 0xFF);
        Serial.write(g & 0xFF);
        Serial.write((b >> 8) & 0xFF);
        Serial.write(b & 0xFF);
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
