int LEDpin[] = {3, 4, 5, 6, 7, 8};
int randomLED;
int ledState = LOW;

unsigned long millisBetweenSelect = 2000;
unsigned long blinkMillis = 100;
unsigned long previousMillisBS;
unsigned long previousMillis;

void setup() {
  //Serial.begin(9600); //uncomment for testing
  for (int i = 0; i < 6; i++) {
    pinMode(LEDpin[i], OUTPUT);
  }
  randomLED = LEDpin[random(0, 6)];
  startupSequence();
  delay(2000);
}

void loop() {
  blinkLED();
}

void blinkLED() {
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillisBS) >= millisBetweenSelect) {
    previousMillisBS = currentMillis;
    digitalWrite(randomLED, LOW);
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
  digitalWrite(randomLED, ledState);
}

void startupSequence() {
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
