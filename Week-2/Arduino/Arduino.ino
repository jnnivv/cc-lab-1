/*
 Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin

// variables will change:
int reading = 0;
int buttonState = 0;         // variable for reading the pushbutton status
int ledState = 0;            // var for storing led
int lastButtonState = 0;     // var for storing the button state in the previous loop
long debounceTimer = 0;      // var holding a timer after the last button state change

float pulse = 0;             // stores button brightness for pulsing (PWM)
float pulseMod = .01;        // modifies brightness each loop iteration

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  reading = digitalRead(buttonPin);
  
  // use debouncing to handle state changes
  if(buttonState != lastButtonState) {
    debounceTimer = millis();
  }
  
  // if button is pressed long enough, trigger state change
  if( millis() - debounceTimer > 40) {
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  
  // apply state to led
  digitalWrite(ledPin, ledState);
  
  // optional: strobe blink
  /*
  // use modulo function (google it!) as a switch for blinking
  if( millis() % 100 > 50 ) {
    digitalWrite(ledPin, ledState);
  } else {
    digitalWrite(ledPin, 0);
  }
  */
  
  // save button state for next iteration
  lastButtonState = buttonState;
}
