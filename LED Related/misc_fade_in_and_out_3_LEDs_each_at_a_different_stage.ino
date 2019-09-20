//fade in and out 3 LEDs each at a different stage

int LEDpin[] = {3, 5, 6};
int fadeAmount = 1;
int brightness[] = {0, 125, 255};

enum {UP, DOWN};

int dimDirection[] = {UP, UP, DOWN};

unsigned long fadeSpeed[] = {};
unsigned long previousMillis;

void setup() {
  Serial.begin(9600); //uncomment for testing
  for (int i = 0; i < 3; i++) {
    pinMode(LEDpin[i], OUTPUT);
    analogWrite(LEDpin[i], 0);
  }
}

void loop() {
  dimLEDs();
}

void dimLEDs() {
  for (int i = 0; i < 3; i++) {
    if (brightness[i] == 255 && dimDirection[i] == UP) {
      dimDirection[i] = DOWN;
    } else if (brightness[i] == 0 && dimDirection[i] == DOWN) {
      dimDirection[i] = UP;
    }
    if (dimDirection[i] == UP) {
      brightness[i] = brightness[i] + fadeAmount;
    } else if (dimDirection[i] == DOWN) {
      brightness[i] = brightness[i] - fadeAmount;
    }
    analogWrite(LEDpin[i], brightness[i]);
    delay(2);
  }
}
