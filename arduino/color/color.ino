#include <Wire.h>
#include "Adafruit_TCS34725.h"

///VARIABLES FOR SERIAL
unsigned char vars[10];
unsigned long x;

///RGB
// some magic numbers for this device from the DN40 application note
#define TCS34725_R_Coef 0.136
#define TCS34725_G_Coef 1.000
#define TCS34725_B_Coef -0.444
#define TCS34725_GA 1.0
#define TCS34725_DF 310.0
#define TCS34725_CT_Coef 3810.0
#define TCS34725_CT_Offset 1391.0

// Autorange class for TCS34725
class tcs34725 {
  public:
    tcs34725(void);

    boolean begin(void);
    void getData(void);

    boolean isAvailable, isSaturated;
    uint16_t againx, atime, atime_ms;
    uint16_t r, g, b, c;
    uint16_t ir;
    uint16_t r_comp, g_comp, b_comp, c_comp;
    uint16_t saturation, saturation75;
    float cratio, cpl, ct, lux, maxlux;

  private:
    struct tcs_agc {
      tcs34725Gain_t ag;
      tcs34725IntegrationTime_t at;
      uint16_t mincnt;
      uint16_t maxcnt;
    };
    static const tcs_agc agc_lst[];
    uint16_t agc_cur;

    void setGainTime(void);
    Adafruit_TCS34725 tcs;
};
//
// Gain/time combinations to use and the min/max limits for hysteresis
// that avoid saturation. They should be in order from dim to bright.
//
// Also set the first min count and the last max count to 0 to indicate
// the start and end of the list.
//
const tcs34725::tcs_agc tcs34725::agc_lst[] = {
  { TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_700MS,     0, 20000 },
  { TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_154MS,  4990, 63000 },
  { TCS34725_GAIN_16X, TCS34725_INTEGRATIONTIME_154MS, 16790, 63000 },
  { TCS34725_GAIN_4X,  TCS34725_INTEGRATIONTIME_154MS, 15740, 63000 },
  { TCS34725_GAIN_1X,  TCS34725_INTEGRATIONTIME_154MS, 15740, 0 }
};
tcs34725::tcs34725() : agc_cur(0), isAvailable(0), isSaturated(0) {
}

// initialize the sensor
boolean tcs34725::begin(void) {
  tcs = Adafruit_TCS34725(agc_lst[agc_cur].at, agc_lst[agc_cur].ag);
  if ((isAvailable = tcs.begin()))
    setGainTime();
  return (isAvailable);
}

// Set the gain and integration time
void tcs34725::setGainTime(void) {
  tcs.setGain(agc_lst[agc_cur].ag);
  tcs.setIntegrationTime(agc_lst[agc_cur].at);
  atime = int(agc_lst[agc_cur].at);
  atime_ms = ((256 - atime) * 2.4);
  switch (agc_lst[agc_cur].ag) {
    case TCS34725_GAIN_1X:
      againx = 1;
      break;
    case TCS34725_GAIN_4X:
      againx = 4;
      break;
    case TCS34725_GAIN_16X:
      againx = 16;
      break;
    case TCS34725_GAIN_60X:
      againx = 60;
      break;
  }
}

// Retrieve data from the sensor and do the calculations
void tcs34725::getData(void) {
  // read the sensor and autorange if necessary

  tcs.getRawData(&r, &g, &b, &c);
  while (1) {
    if (agc_lst[agc_cur].maxcnt && c > agc_lst[agc_cur].maxcnt)
      agc_cur++;
    else if (agc_lst[agc_cur].mincnt && c < agc_lst[agc_cur].mincnt)
      agc_cur--;
    else break;

    setGainTime();
    delay((256 - atime) * 2.4 * 2); // shock absorber
    tcs.getRawData(&r, &g, &b, &c);
    break;
  }

  // DN40 calculations
  ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;
  r_comp = r - ir;
  g_comp = g - ir;
  b_comp = b - ir;
  c_comp = c - ir;
  cratio = float(ir) / float(c);

  saturation = ((256 - atime) > 63) ? 65535 : 1024 * (256 - atime);
  saturation75 = (atime_ms < 150) ? (saturation - saturation / 4) : saturation;
  isSaturated = (atime_ms < 150 && c > saturation75) ? 1 : 0;
  cpl = (atime_ms * againx) / (TCS34725_GA * TCS34725_DF);
  maxlux = 65535 / (cpl * 3);

  lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
  ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;
}

tcs34725 rgb_sensor;
///END RGB

void setup() {
  Serial.begin(1000000);
  rgb_sensor.begin();
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
        rgb_sensor.getData();  
        Serial.write((rgb_sensor.r_comp >> 8) & 0xFF);
        Serial.write(rgb_sensor.r_comp & 0xFF);
        Serial.write((rgb_sensor.g_comp >> 8) & 0xFF);
        Serial.write(rgb_sensor.g_comp & 0xFF);
        Serial.write((rgb_sensor.b_comp >> 8) & 0xFF);
        Serial.write(rgb_sensor.b_comp & 0xFF);
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
