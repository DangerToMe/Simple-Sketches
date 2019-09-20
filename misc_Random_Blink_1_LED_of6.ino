//randomly blink one of six LEDs
int LEDpin[] = {3, 4, 5, 6, 7, 8}; //LEDs are connected to these pins
int randomLED;
int ledState = LOW;

unsigned long millisBetweenSelect = 2000; //length of time in millis to blink each selection
unsigned long blinkMillis = 100; //blink speed in millis
unsigned long previousMillisBS;
unsigned long previousMillis;

void setup() {
  //set pinMode for all six ledPins
  for (int i = 0; i < 6; i++) {
    pinMode(LEDpin[i], OUTPUT);
  }
  //choose a random pin to start with 
  randomLED = LEDpin[random(0, 6)]; //(always picks the second LED first time)
  startupSequence(); //just a wee bit of flair
  delay(2000);
}

void loop() {
  blinkLED();
}

void blinkLED() {
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillisBS) >= millisBetweenSelect) {
    previousMillisBS = currentMillis;
    //set the current LED to LOW
    digitalWrite(randomLED, LOW);
    //choose the next random LED
    randomLED = LEDpin[random(0, 6)];
  }
  if ((currentMillis - previousMillis) >= blinkMillis) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  //set the current LED's state (HIGH or LOW)
  digitalWrite(randomLED, ledState);
}

void startupSequence() {
  //the wee bit of flair
  for (int i = 0; i < 6; i++) {
    digitalWrite(LEDpin[i], HIGH);
    delay(100);
    digitalWrite(LEDpin[i], LOW);
  }
  for (int i = 4; i >= 0; i--) {
    digitalWrite(LEDpin[i], HIGH);
    delay(100);
    digitalWrite(LEDpin[i], LOW);
  }
}
