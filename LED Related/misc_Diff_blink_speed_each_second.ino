//Blinks the onboard LED at a different random rate each second.
//Written as a challenge to myself (albeit a small one)


int LEDpin = 13; //tied to onboard LED
int ledState = LOW;

unsigned long intervalTime = 1000; //interval between changing random blink times
unsigned long blinkDelay[] = {50, 100, 200, 500}; //millis between blinks. All divide evenly into 1000
unsigned long randomDelay;
unsigned long previousMillis;
unsigned long previousMillisSecond;

void setup() {
  Serial.begin(9600); // for testing
  pinMode(LEDpin, OUTPUT);
  randomDelay = blinkDelay[random(0, 4)];
}

void loop() {
  unsigned long currentMillis = millis();
  //check to see if interval time has expired
  if ((currentMillis - previousMillisSecond) >= intervalTime) {
    //if it has, select a new random delay
    randomDelay = blinkDelay[random(0, 4)];
    //reset for the next interval
    previousMillisSecond = currentMillis;
    Serial.println(randomDelay); //to see which random delay is being ran
  }

  //check to see if delay time has expired
  if ((currentMillis - previousMillis) >= randomDelay) {
    //reset for next delay
    previousMillis = currentMillis;
    //switch the LED state
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  digitalWrite(LEDpin, ledState);
}
