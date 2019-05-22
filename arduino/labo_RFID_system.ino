//RFID Initialization
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"


// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define NFC_IRQ   (2)
#define NFC_RESET (3)  

// Or use this line for a breakout or shield with an I2C connection:
Adafruit_PN532 nfc(NFC_IRQ, NFC_RESET);

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
// also change #define in Adafruit_PN532.cpp library file
   #define Serial SerialUSB
#endif

// Ultrasonic Initialization
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// const int LED = 7;
// defines variables
long duration;
int distance;

static const uint8_t PROGMEM
  one[] =
  { B00001100,
    B00011100,
    B00111100,
    B01101100,
    B00001100,
    B00001100,
    B11111111,
    B11111111 },  
  two[] = 
  { B00011000,
    B00111110,
    B01100110,
    B01100110,
    B00001100,
    B00011000,
    B10111111,
    B10111111 },
  three[] = 
  { B00011110,
    B00111111,
    B00110011,
    B00000011,
    B00001110,
    B00000011,
    B00110011,
    B00111111 },
  four[] =
  { B01100000,
    B01100000,
    B01101100,
    B01101100,
    B11111111,
    B11111111,
    B00001100,
    B00001100 },
  blank[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  cross[] =
  { B11000000,
    B00100001,
    B00010010,
    B00001100,
    B00001100,
    B00010010,
    B00100001,
    B11000000 },
  frown_bmp[] =
  { B00011110,
    B00100001,
    B11010010,
    B11000000,
    B11001100,
    B11010010,
    B00100001,
    B00011110 },
  smile_bmp[] =
  { B00011110,
    B00100001,
    B11010010,
    B11000000,
    B11010010,
    B11001100,
    B00100001,
    B00011110 },
  arrow[] =
  { B00000100,
    B00000110,
    B00000011,
    B11111111,
    B11111111,
    B00000011,
    B00000110,
    B00000100 };

void setup() {
  // Ultrasonic 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // LED
  // pinMode(LED, OUTPUT);

  // RFID
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  
  Serial.begin(9600);

  nfc.begin();

  matrix.begin(0x70);  

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find NFC sensor board");
    while (1); // halt
  }

  // Serial.println("Sensor ready!");
  
  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  nfc.setPassiveActivationRetries(0xFF);

  // configure board to read RFID tags
  nfc.SAMConfig();

  // Serial.println("Show us your card!");

}

void loop() {
  // RFID 
  boolean detector;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID from tag
  
  uint8_t obj1[] = {0x56, 0x54, 0x4A, 0x42};
  uint8_t obj2[] = {0x26, 0x54, 0x4A, 0x42};
  uint8_t obj3[] = {0xF6, 0x53, 0x4A, 0x42};
  uint8_t obj4[] = {0xD6, 0x52, 0x4A, 0x42};
  
  uint8_t uidLength;

  //LED
  // digitalWrite(LED, LOW);
  // Ultrasonic
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(100); 
  
  if(distance<=20){
    // LED lights on
   // digitalWrite(LED, HIGH);
  
    for(int8_t x=0; x>=-20; x--){
      matrix.clear();
      matrix.drawBitmap(0, 0, cross, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(100);     

      matrix.clear();
      matrix.drawBitmap(0, 0, blank, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(100);
    }

    matrix.clear();
    matrix.drawBitmap(0, 0, arrow, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(100);
   // Serial.println("Object detected!");
    // Serial.println("Moving closer....");

    while(distance>=2){
      // digitalWrite(LED, HIGH);   
      // delay(1000);                     
      // digitalWrite(LED, LOW);    
      // delay(1000); 
      distance = (pulseIn(echoPin, HIGH))*0.034/2;
      Serial.print("Distance: ");
      Serial.println(distance);
      detector = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
      
      if(detector){
        break;
      }
    } // while loop closed
    
    // digitalWrite(LED, HIGH);
    if(detector){
      Serial.println("Found a tag!");
      // Stop robot

      Serial.println("This is .....");
      if(memcmp(obj1, uid, 4) == 0){
        Serial.println("Object 1");

        matrix.clear();
        matrix.drawBitmap(0, 0, one, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(1000);
      }
      
      else if (memcmp(obj2, uid, 4) == 0){
        Serial.println("Object 2");
        matrix.clear();
        matrix.drawBitmap(0, 0, two, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(1000);
      }

      else if(memcmp(obj3, uid, 4) == 0){
        Serial.println("Object 3");
        matrix.clear();
        matrix.drawBitmap(0, 0, three, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(1000); 
      }

      else if(memcmp(obj4, uid, 4) == 0){
        Serial.println("Object 4");
        matrix.clear();
        matrix.drawBitmap(0, 0, four, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(1000);
      }
      
      else{
        Serial.println("Not in database");
        matrix.clear();
        matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();
        delay(1000);
      }
    
      delay(5000); 
  
    }
    else{
      Serial.println("SToooooooPPPPP");    
    }
  }
}

  
