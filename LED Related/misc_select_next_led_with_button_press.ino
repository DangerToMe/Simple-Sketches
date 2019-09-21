//Select random LED with button press

int currentPin = 0;
int arraySize;
int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

const int buttonPin = 11;
const int ledPins[] = {3, 5, 6, 7, 8, 9}; //pin 4 on my uno is giving odd results

unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

void setup() {
  arraySize = sizeof( ledPins ) / sizeof( int );
  for (int i = 0; i < arraySize; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPins[currentPin], HIGH);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // turn off all LEDs and select a new one
      if (buttonState == HIGH) {
        for (int i = 0; i < arraySize; i++) {
          digitalWrite(ledPins[i], LOW);
        }
        if(currentPin == arraySize-1){
          currentPin = 0;
        }else{
          currentPin++;
        }
      }
    }
  }
  // set the LED:
  digitalWrite(ledPins[currentPin], HIGH);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
