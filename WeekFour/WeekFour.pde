import processing.serial.*;
import cc.arduino.*;

Arduino arduino;

int hiddenX;
int hiddenY;

void setup() {
  size(600, 600);
  // Prints out the available serial ports.
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[3], 57600);
  
  hiddenX = (int) random(0, width);
  hiddenY = (int) random(0, height);
}

void draw() {
  
  int distance = (int) dist(mouseX, mouseY, hiddenX, hiddenY);
  
  // if found, generate new location
  if( distance < 10 ) {
    hiddenX = (int) random(0, width);
    hiddenY = (int) random(0, height);
  }
  
  arduino.digitalWrite(8, 1);
  delay(distance);
  arduino.digitalWrite(8, 0);
  delay(distance);
}