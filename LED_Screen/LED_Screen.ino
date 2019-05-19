#include <EEPROM.h> //a memory which can store data even when the board is off;

#include <UTFT.h>
#include <URTouch.h>
#include "pitches.h"


//page0=smiley face
//page1=main screen
//page2=flappy bird
//page3=restartGame page
//page4=Notepad page
//page5=music
 



//==== Creating Objects
//model is 240*320 (y and x)
UTFT    myGLCD(ILI9341_16, 38, 39, 40, 41); //the model mode is ILI9341_16,
URTouch  myTouch( 6, 5, 4, 3, 2);
//==== Defining Variables
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

boolean input = false;
char currentPage;
int count = 10000; // this is set to 1 minute
int x, y; //touch screen coordination
extern unsigned int bird01[0x41A];

// Flappy Bird
int xP = 319; // varaibel where we can draw the pillar
int yP = 100; //this is also the variable which we use to draw the pillar, 100 is the height of the first pillar
int yB = 50;  //y coordinate of the bird
int movingRate = 3; //the speed of the bird
int fallRateInt = 0; //falling rate
float fallRate = 0;
int score = 0;
int lastSpeedUpScore = 0;
int highestScore;
boolean screenPressed = false;
boolean gameStarted = false;

//tone
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
extern unsigned int ButtonPlay[0x1AE9];

void setup() {
  // Initial setup
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myGLCD.fillScr(255, 255, 255); //set color of the screen to white
  smiley_face();  // Draws the Home Screen
  currentPage = '0'; // Indicates that we are at Home Screen
  highestScore = EEPROM.read(0); // Read the highest score from the EEPROM

}

// drawMainScreen - Custom Function
void drawMainScreen() {
  // Title
  myGLCD.fillScr(255, 255, 255); //set color of the screen to white
  myGLCD.setBackColor(255, 255, 255); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(0, 0, 0); // Sets color to black
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("How can I help you?", CENTER, 5); // Prints the string on the screen
  myGLCD.setColor(0, 0, 0); // Sets color to black
  myGLCD.drawLine(0, 25, 319, 25); // Draws the black line
  myGLCD.setColor(0, 0, 0); // Sets color to black
  myGLCD.setFont(SmallFont); // Sets the font to small
  myGLCD.print("by Cornell Cup Robotics", CENTER, 41); // Prints the string
  myGLCD.setFont(BigFont); // Sets the font to small
  myGLCD.print("Select", CENTER, 64);

  // Button - Notepad
  myGLCD.setColor(248, 255, 178); // Sets yellowish color
  myGLCD.fillRoundRect (35, 90, 285, 130); // Draws filled rounded rectangle
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect (35, 90, 285, 130); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(248, 255, 178); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("Note", CENTER, 102); // Prints the string

  // Button - Music
  myGLCD.setColor(243, 213, 238); //set the color to pinkish color
  myGLCD.fillRoundRect (35, 140, 285, 180);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect (35, 140, 285, 180);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(243, 213, 238);
  myGLCD.print("MUSIC", CENTER, 152);

  // Button - Game--flappy bird
  myGLCD.setColor(178, 235, 255);
  myGLCD.fillRoundRect (35, 190, 285, 230);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect (35, 190, 285, 230);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(178, 235, 255);
  myGLCD.print("GAME", CENTER, 202);
}

void smiley_face() {
  myGLCD.setColor(14, 17, 102); // Sets purpleish color
  myGLCD.fillCircle (80, 80, 10); // Draws filled circle
  myGLCD.setColor(14, 17, 102);
  myGLCD.fillCircle (240, 80, 10); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setColor(14, 17, 102);
  myGLCD.fillRoundRect (100, 190, 220, 200); //a straight line for the mouth
  myGLCD.setColor(14, 17, 102);
  myGLCD.fillRoundRect (100, 200, 110, 150);
  myGLCD.setColor(14, 17, 102);
  myGLCD.fillRoundRect (210, 150, 220, 200);

}

//highlight the button when pressed
void drawFrame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(16, 125, 8); //set the color to green
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255); //set the color to white
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}
// ===== initiateGame - Custom Function
void initiateGame() {
  myGLCD.clrScr();
  // Blue background
  myGLCD.setColor(114, 198, 206); //set the color to blue
  myGLCD.fillRect(0, 0, 319, 239);
  // Ground
  myGLCD.setColor(221, 216, 148);
  myGLCD.fillRect(0, 215, 319, 239);
  myGLCD.setColor(47, 175, 68);
  myGLCD.fillRect(0, 205, 319, 214);
  // Text
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.print("Score:", 5, 220);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Cornell Cup Robotics", 140, 220);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(114, 198, 206);
  myGLCD.print("Highest Score: ", 5, 5);
  myGLCD.printNumI(highestScore, 120, 6);
  myGLCD.print("RESET", 255, 5);
  myGLCD.drawLine(0, 23, 319, 23);
  myGLCD.print("TAP TO START", CENTER, 100);

  drawBird(yB); // Draws the bird

  // Wait until we tap the sreen
  while (!gameStarted) {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      // Reset higest score
      if ((x >= 250) && (x <= 319) && (y >= 0) && (y <= 28)) {
        highestScore = 0;
        myGLCD.setColor(114, 198, 206);
        myGLCD.fillRect(120, 0, 150, 22);
        myGLCD.setColor(0, 0, 0);
        myGLCD.printNumI(highestScore, 120, 5);
      }
      if ((x >= 0) && (x <= 319) && (y >= 30) && (y <= 239)) {
        gameStarted = true;
        myGLCD.setColor(114, 198, 206);
        myGLCD.fillRect(0, 0, 319, 32);
      }
    }
  }
  // Clears the text "TAP TO START" before the game start
  myGLCD.setColor(114, 198, 206);
  myGLCD.fillRect(85, 100, 235, 116);

}

//Playing the game Flappy Bird
void drawBird(int y) {
  if (y <= 219) {
    myGLCD.drawBitmap (50, y, 35, 30, bird01);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRoundRect(50, y, 85, y - 6);
    myGLCD.fillRoundRect(50, y + 30, 85, y + 36);
  }
  else if (y >= 200) {
    myGLCD.drawBitmap (50, 200, 35, 30, bird01);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRoundRect(50, 200, 85, 200 - 6);
    myGLCD.fillRoundRect(50, 200 + 30, 85, 200 + 36);
  }
}

void undrawBird(int y) {
  if (y <= 219) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRoundRect(50, y, 85, y - 6);
    myGLCD.fillRoundRect(50, y + 30, 85, y + 36);
  }
  else if (y >= 200) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRoundRect(50, 200, 85, 200 - 6);
    myGLCD.fillRoundRect(50, 200 + 30, 85, 200 + 36);
  }
}

void drawGround() {
  myGLCD.setColor(221, 216, 148);
  myGLCD.fillRect(0, 215, 319, 239);
  myGLCD.setColor(47, 175, 68);
  myGLCD.fillRect(0, 205, 319, 214);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.print("Score:", 5, 220);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Cornell Cup Robotics", 140, 220);
}

void drawPilars(int x, int y) {
  if (x >= 270) {
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(318, 0, x, y - 1);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(319, 0, x - 1, y);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(318, y + 81, x, 203);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(319, y + 80, x - 1, 204);
  }
  else if ( x <= 268) {
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x + 51, 0, x + 53, y);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x + 49, 1, x + 1, y - 1);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x + 50, 0, x, y);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x - 1, 0, x - 3, y);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x + 51, y + 80, x + 53, 204);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x + 49, y + 81, x + 1, 203);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x + 50, y + 80, x, 204);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x - 1, y + 80, x - 3, 204);
  }
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(score, 100, 220);
}


void gameOver() {
  currentPage = '3';
  myGLCD.clrScr();
  //Game Over
  myGLCD.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to black
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Game Over", CENTER, 40); // Prints the string on the screen
  //Score
  myGLCD.print("Score:", 100, 80);
  myGLCD.printNumI(score, 200, 80);
  // Restart the Game
  myGLCD.setColor(0, 0, 0); // Sets black
  myGLCD.fillRoundRect (35, 140, 285, 180); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 140, 285, 180); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setColor(255, 255, 255); //set the font to white
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("Restart", CENTER, 150); // Prints the string

  //Go back to main Screen
  myGLCD.setColor(0, 0, 0); // Sets the color to black
  myGLCD.fillRoundRect (35, 190, 285, 230); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 190, 285, 230); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Main Screen", CENTER, 200); // Prints the string
  if (score > highestScore) {
    highestScore = score;
    EEPROM.write(0, highestScore);
  }
  while (currentPage == '3') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      //if the main screen button is pressed
      if (((x >= 35) && (x <= 285) ) && ((y >= 10) && (y <= 50))) {
        currentPage = '1';
        gameStarted = false;
        xP = 319;
        yB = 30;
        fallRate = 0;
        score = 0;
        myGLCD.clrScr();
        drawMainScreen();
        delay(1000);
      }
      //when user wants to restart the game
      else if (((x >= 35) && (x <= 285) ) && ((y >= 70) && (y <= 100))) {
        gameStarted = false;
        currentPage = '2';
        xP = 319;
        yB = 30;
        fallRate = 0;
        score = 0;
        initiateGame();
        delay(1000);
      }

    }
  }

}

void drawPalatte() {
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(247, 10, 121); // Sets to kind of magenta
  myGLCD.fillRect (0, 0, 40, 40);
  myGLCD.setColor(10, 200, 247); // Sets to kind of sky blue
  myGLCD.fillRect (0, 40, 40, 80);
  myGLCD.setColor(67, 161, 61); // Sets to greenish color
  myGLCD.fillRect (0, 80, 40, 120);
  //Back Button
  myGLCD.setBackColor(255, 255, 255); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(0, 0, 0); // Sets black
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back", RIGHT, 8);
  myGLCD.drawRoundRect (285, 2, 319, 25 );
  myGLCD.setColor(0, 0, 0);
  //Clear Button
  myGLCD.setBackColor(255, 255, 255); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(0, 0, 0); // Sets black
  myGLCD.setFont(SmallFont);
  myGLCD.print("Clear", RIGHT, 47);
  myGLCD.drawRoundRect (275, 39, 319, 62 );
  myGLCD.setColor(0, 0, 0);

}

void playMusic() {
  myGLCD.clrScr();
  myGLCD.drawBitmap (118, 79, 83, 83, ButtonPlay);//(118,79,201,162), 83 is the width and the height of the bitmap
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(0, 0, 75, 28);
  myGLCD.setBackColor(0, 0, 0); //set color to be black
  myGLCD.setColor(255, 255, 255); // text to be white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("BACK", 5, 5); // Prints the string on the screen

}

void loop() {
  //on the smiley face screen
  if (currentPage == '0') {
    if (myTouch.dataAvailable()) { //check to see if new data is being available
      drawMainScreen(); // draw the Main functional screen
      currentPage = '1'; // Indicates that we are in the main functional screen
      /*while(currentPage=='1' && count>=0){ //start a timer that counts down from 1 minutes, if it reaches 0, it will go back to page 0.
        if (!myTouch.dataAvailable()){}
        count--;
        }
        //go back to the main screen
        myGLCD.clrScr(); //set the page to the black
        myGLCD.fillScr(255,255,255); //fill the screen with white
        smiley_face();
        currentPage='0';
        count=10000;
      */

    }
  }

  //on the main functional screen
  if (currentPage == '1') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if (((x >= 35) && (x <= 285) ) && ((y >= 10) && (y <= 50))) {
        drawFrame(35, 190, 285, 230); //highlight button when it is pressed
        currentPage = '2';
        initiateGame(); // Initiate the game
        delay(1000);
      }
      else if (((x >= 35) && (x <= 285) ) && ((y >= 110) && (y <= 150))) {
        drawPalatte();
        currentPage = '4';
        delay(1000);
      }
      else if (((x >= 35) && (x <= 285) ) && ((y >= 60) && (y <= 100))) {
        currentPage = '5';
        playMusic();
        delay(1000);
      }

    }
  }

  //for the flappy bird game
  if (currentPage == '2') {
    //delay(1);
    xP = xP - movingRate; //the x coordinate of the pillar
    drawPilars(xP, yP);

    yB += fallRateInt; //the position of the bird
    fallRate = fallRate + 0.4; //the bird is falling faster and faster
    fallRateInt = int(fallRate);
    if (yB >= 220) {
      yB = 220;
    }
    //check for collision
    if (yB >= 180 || yB <= 0) { //top and bottom
      gameOver();
    }
    //top pillar
    if ((xP <= 85) && (xP >= 30) && (yB <= yP - 2)) {
      gameOver();

    }
    //lower pillar
    if ((xP <= 85) && (xP >= 30) && (yB >= yP + 60)) {
      gameOver();
    }
    if (gameStarted == true) {
      drawBird(yB);
    }
    if (xP <= -51) {
      xP = 319;
      yP = rand() % 100 + 20;
      score++;
    }

    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 0) && (x <= 319) && (y >= 50) && (y <= 239)) {
        fallRate = -5;
      }
    }


    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 10) && (x <= 60) && (y >= 10) && (y <= 36)) {
        drawFrame(10, 10, 60, 36);
        currentPage = '0';
        myGLCD.clrScr();
        drawMainScreen();
      }
    }
  }
  if (currentPage == '4') {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    //if pick the magenta color
    if ((x >= 0) && (x <= 40) && (y >= 200 ) && (y <= 239 )) {
      //while the other colors are not chosen
      while (!((x >= 0) && (x <= 40) && (y >= 120 ) && (y <= 200))) {
        myTouch.read();
        x = myTouch.getX();
        y = myTouch.getY();
        myGLCD.setColor(247, 10, 121);
        myGLCD.fillCircle(x, 240 - y, 4);
        //when the back button is pressed
        if ((x >= 285) && (x <= 319) && (y >= 214 ) && (y <= 237)) {
          currentPage = '1';
          myGLCD.clrScr();
          drawMainScreen();
          break;
        }
        //when the clear button is pressed
        if ((x >= 275) && (x <= 319) && (y >= 177 ) && (y <= 200)) {
          myGLCD.clrScr();
          drawPalatte();
        }
      }
    }
    //if pick the blue color
    if ((x >= 0) && (x <= 40) && (y >= 160 ) && (y <= 200)) {
      //while the other colors are not chosen
      while (!((x >= 0) && (x <= 40) && (y >= 200 ) && (y <= 239 )) && !((x >= 0) && (x <= 40) && (y >= 120 ) && (y <= 160))) {
        myTouch.read();
        x = myTouch.getX();
        y = myTouch.getY();
        myGLCD.setColor(10, 200, 247);
        myGLCD.fillCircle(x, 240 - y, 4);
        if ((x >= 285) && (x <= 319) && (y >= 214 ) && (y <= 237)) {
          currentPage = '1';
          myGLCD.clrScr();
          drawMainScreen();
          break;
        }
        //when the clear button is pressed
        if ((x >= 275) && (x <= 319) && (y >= 177 ) && (y <= 200)) {
          myGLCD.clrScr();
          drawPalatte();
        }
      }
    }
    //if pick the green color
    if ((x >= 0) && (x <= 40) && (y >= 120 ) && (y <= 160)) {
      //while the other colors are not chosen
      while (!((x >= 0) && (x <= 40) && (y >= 160 ) && (y <= 239))) {
        myTouch.read();
        x = myTouch.getX();
        y = myTouch.getY();
        myGLCD.setColor(67, 161, 61);
        myGLCD.fillCircle(x, 240 - y, 4);
        if ((x >= 285) && (x <= 319) && (y >= 214 ) && (y <= 237)) {
          currentPage = '1';
          myGLCD.clrScr();
          drawMainScreen();
          break;
        }
        //when the clear button is pressed
        if ((x >= 275) && (x <= 319) && (y >= 177 ) && (y <= 200)) {
          myGLCD.clrScr();
          drawPalatte();
        }
      }
    }

  }
  if (currentPage == '5') {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    //If back button is pressed
    if ((x >= 0) && (x <= 75) && (y >= 211) && (y <= 239)) {
      currentPage='1';
      drawMainScreen();
      }
    //when the play button is pressed
    if ((x >= 118) && (x <= 201) && (y >= 78) && (y <= 161)) {
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);

      }
    }
  }
}

















