/*  SevenSegmentLEDdisplay102a.ino
 *   2017-02-20
 *   Mel Lester Jr.
 *  Simple example of using Shift Register with a
 *  Single Digit Seven Segment LED Display
*/

#include "pitches.h"

// Globals
const int dataPin = 4;  // blue wire to 74HC595 pin 14
const int latchPin = 3; // green to 74HC595 pin 12
const int clockPin = 2; // yellow to 74HC595 pin 11
const int piezoPin = 8;
const int potiPin = A0;
const int btnPin = 9;

bool lastBtnState = 0;
long pressTime = 0;
bool mode = 0;          // 0: train, 1: test
bool click = 0;         // becomes 1 after a click was registered

int i = 0;
int testModeState = 0;
 
void setup() {
  // initialize I/O pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read sensors
  int poti = map(analogRead(potiPin), 0, 1024, 0, 8);
  bool btn = digitalRead(btnPin);
  // record button clicks
  if(btn == 1 && lastBtnState == 0) {
    pressTime = millis();
  }
  // button press duration
  int duration =  millis() - pressTime;
  // handle button clicks
  if(btn == 0 && lastBtnState == 1 && duration > 50 && duration < 2000) {
    click = 1;
  }
  // handle button long press -> switch mode
  if(duration > 2000 && btn == 1) {
    mode = !mode;
    pressTime = millis();
  }


  // TRAINING MODE
  if(mode==0) {
    if(click) {
      // generate random digit
      i = (int) random(0,8);
    }
    // calculate bytes for shift register
    byte bits = numToBits(i);
    // display digit
    updateDisplay(bits);
    // play tone
    tone(piezoPin, numToTone(i), 100);
    delay(100);
    noTone(piezoPin);
  
  
  // TEST MODE
  } else {
    // new test number
    if(testModeState == 0) {
      i = (int) random(0,8);  
      testModeState++;
    }
    
    // play sound
    tone(piezoPin, numToTone(i), 100);
    delay(100);
    noTone(piezoPin);
    
    // calculate bytes for shift register
    byte bits = numToBits(poti);
    // display digit
    updateDisplay(bits);
   
   // click (=submit) -> check if right number
   if(click) {
     if(poti == i) {
       correctAnim();
       testModeState = 0; 
     } else {
       falseAnim();
     }
   }
  }
  
  
  lastBtnState = btn;
  click = 0;
}

// update shift register
void updateDisplay(byte eightBits) {
  eightBits = eightBits ^ B11111111;  // flip all bits using XOR 
  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}

// lookup function for digit byte codes
byte numToBits(int output) {
  switch (output) {
    case 0:
      return B10001011; //C
      break;
    case 1:
      return B10000001; //D
      break;
    case 2:
      return B00001011; //E
      break;
    case 3:
      return B00101011; //F
      break;
    case 4:
      return B00000011; //G
      break;
    case 5:
      return B00100001; //A
      break;
    case 6:
      return B00000001; //B
      break;
    case 7:
      return B10001011; //C
      break;
    default:
      return B01011011; // Error condition, displays three vertical bars
      break;   
  }
}

// lookup function for digit tones
int numToTone(int output) {
  switch (output) {
    case 0:
      return NOTE_C4;
      break;
    case 1:
      return NOTE_D4;
      break;
    case 2:
      return NOTE_E4;
      break;
    case 3:
      return NOTE_F4;
      break;
    case 4:
      return NOTE_G4;
      break;
    case 5:
      return NOTE_A4;
      break;
    case 6:
      return NOTE_B4;
      break;
    case 7:
      return NOTE_C5;
      break;
    case 10:
      return NOTE_C1;
      break;
    case 11:
      return NOTE_C1;
      break;
    default:
      return NOTE_C1; // Error condition, displays three vertical bars
      break;   
  }
}


// plays an animation when guess correct
void correctAnim() {
  updateDisplay(B10001011);
  delay(300);
  updateDisplay(B11111111);
  delay(300);
  updateDisplay(B10001011);
  delay(300);
  updateDisplay(B11111111);
  delay(300);
  updateDisplay(B10001011);
  delay(300);
  updateDisplay(B11111111);
}

// plays an animation when guess wrong
void falseAnim() {
  updateDisplay(B11111111);
  delay(75);
  updateDisplay(B10111111);
  delay(75);
  updateDisplay(B11011111);
  delay(75);
  updateDisplay(B11110111);
  delay(75);
  updateDisplay(B11111101);
  delay(75);
  updateDisplay(B11111011);
  delay(75);
  updateDisplay(B11101111);
  delay(75);
  updateDisplay(B01111111);
  delay(75);
  updateDisplay(B00101011);
  delay(1000);
}
