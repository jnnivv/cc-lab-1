// assign pins
const int ledPin = 2;
const int tiltPin = 3;
const int potiPin = A0;

int steps = 0;
boolean tiltState = 0;
boolean tilt = 0;
long stepTime = 0;
long lastStepTime = 0;

int stepInterval = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read current tilt
  tilt = digitalRead(tiltPin);
  // update interval timer according to poti
  stepInterval = map(analogRead(A0), 0, 1024, 100, 2000);
  
  // debouncing, to remove ... bouncy walking
  if(tilt != tiltState) {
    stepTime = millis();
  }
  
  // increment steps after debouncing
  if( millis() - stepTime > 40 ) {
    tiltState = tilt;
    steps++;
    tiltState = !tiltState;
    // record time of current step
     lastStepTime = millis();
    Serial.println(steps);
  }
  
  // control LED
  // turn on if last step was too long ago
  if( millis() - lastStepTime > stepInterval ) {
    digitalWrite(ledPin, HIGH);
  // turn off if walking fast enough
  } else {
    digitalWrite(ledPin, LOW);  
  }
  
}
