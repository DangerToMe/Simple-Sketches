//Blinks a set amount of LEDs chosen at random
//with random blink speeds

//Has a bug. Occasionally, it only blinks one LED. Not sure what
//that's all about. But I'll revisit this script later.

int ledPins[] = {3, 5, 6, 7, 8, 9};
int blinkHowMany = 2;
int ledsChosen = 0;
int selectedPins[] = {0, 0, 0, 0, 0, 0};
int ledState[] = {LOW, LOW, LOW, LOW, LOW, LOW};
int getNew = 0;
int arrayIndex = 0;

unsigned long pickRandom = 2000; //milliseconds between reselecting random pins and blink times
unsigned long randomMillis;
unsigned long blinkTimes[] = {50, 100, 250, 500};
unsigned long previousMillis[] = {0, 0, 0, 0, 0, 0};
unsigned long selectedTimes[] = {0, 0, 0, 0, 0, 0};

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  blinkLEDs();
}

void chooseLEDs() {
  int randomLED = ledPins[random(0, 6)];
  for (int i = 0; i < blinkHowMany; i++) {
    if (randomLED == selectedPins[i]) {
      getNew = 1;
    }
  }
  if (getNew == 1) {
    blinkLEDs();
  }
  if (getNew == 0) {
    selectedPins[arrayIndex] = randomLED;
    int randomTime = blinkTimes[random(0, 4)];
    selectedTimes[arrayIndex] = randomTime;
    arrayIndex++;
    if (arrayIndex == blinkHowMany) {
      arrayIndex = 0;
    }
    ledsChosen++;
  }
}

void blinkLEDs() {
  if (ledsChosen < blinkHowMany) {
    getNew = 0;
    chooseLEDs();
  } else {
    unsigned long currentMillis = millis();
    if ((currentMillis - randomMillis) >= pickRandom) {
      randomMillis = currentMillis;
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
        ledState[i] = LOW;
      }
      ledsChosen = 0;
      chooseLEDs();
    }
    for (int i = 0; i < blinkHowMany; i++) {
      if ((currentMillis - previousMillis[i]) >= selectedTimes[i]) {
        previousMillis[i] = currentMillis;
        if (ledState[i] == LOW) {
          ledState[i] = HIGH;
        } else {
          ledState[i] = LOW;
        }
        digitalWrite(selectedPins[i], ledState[i]);
      }
    }
  }
}
