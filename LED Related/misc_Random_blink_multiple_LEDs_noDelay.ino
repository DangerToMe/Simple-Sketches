//Blinks a set amount of LEDs chosen at random from 6 pins
//with random blink speeds

int ledPins[] = {3, 5, 6, 7, 8, 9};
int numToBlink = 2;
int ledsChosen = 0;
int selectedPins[] = {0, 0, 0, 0, 0, 0};
int ledState[] = {LOW, LOW, LOW, LOW, LOW, LOW};
int getNew = 0;
int pinIndex = 0;
int timeIndex = 0;
int arraySize;

unsigned long pickRandom = 2000; //milliseconds between reselecting random pins and blink times
unsigned long randomMillis;
unsigned long blinkTimes[] = {50, 100, 250, 500};
unsigned long previousMillis[] = {0, 0, 0, 0, 0, 0};
unsigned long selectedTimes[] = {0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  selectRandomPins();
  selectRandomTimes();
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.println("Select Carriage return below to chnge number of LEDs to blink");
  arraySize = sizeof( ledPins ) / sizeof( int );
}

void loop() {
  if ( Serial.available () > 0 ) {
    static char input[16];
    static uint8_t i;
    char c = Serial.read ();
    if ( c != '\r' && i < 15 ) { // assuming "Carriage Return" is chosen in the Serial monitor as the line ending character
      input[i++] = c;
    } else {
      input[i] = '\0';
      i = 0;
      int number = atoi( input );
      //if number is equal to or greater than the number of LEDs being used,
      //my Arduino hangs and has to be restarted. So, insure that doesn't happen
      if (number >= arraySize) {
        numToBlink = arraySize - 1;
        Serial.print(numToBlink);
        Serial.println(" is the maximum allowed.");
      } else {
        numToBlink = number;
      }
    }
  }
  checkSelectionInterval();
}

void selectRandomPins() {
  while (pinIndex < numToBlink) {
    getNew = 0;
    int randomPin = ledPins[random(0, 6)];
    for (int i = 0; i < numToBlink; i++) {
      if (randomPin == selectedPins[i]) {
        getNew = 1;
      }
    }
    if (getNew == 0) {
      selectedPins[pinIndex] = randomPin;
      pinIndex++;
    }
  }
}

void selectRandomTimes() {
  timeIndex = 0;
  while (timeIndex < numToBlink) {
    unsigned long randomTime = blinkTimes[random(0, 4)];
    selectedTimes[timeIndex] = randomTime;
    timeIndex++;
  }
}

void checkSelectionInterval() {
  unsigned long currentMillis = millis();
  if ((currentMillis - randomMillis) >= pickRandom) {
    randomMillis = currentMillis;
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], LOW);
      ledState[i] = LOW;
    }
    pinIndex = 0;
    selectRandomPins();
    selectRandomTimes();
  }
  blinkLEDs();
}

void blinkLEDs() {
  unsigned long currentMillis = millis();
  for (int i = 0; i < numToBlink; i++) {
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
