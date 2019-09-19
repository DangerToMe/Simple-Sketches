//Compiles but NOT TESTED
//Code to blink an LED at one speed if the
//button is held pressed. And at a different
//speed when the button is not held pressed

const int buttonPin = 7;
const int ledPin = 8;

unsigned long previousMillis;
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;    

unsigned long intervalLong = 500;
unsigned long intervalShort = 100;

int buttonState = LOW;
int ledState = LOW;
int lastButtonState = LOW;

void setup() {
   pinMode(ledPin, OUTPUT);
   pinMode(buttonPin, INPUT);
   digitalWrite(ledPin, ledState);
   digitalWrite(buttonPin, buttonState);
}

void loop(){
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == HIGH) {
                blinkLed(intervalShort);
            } else {
              blinkLed(intervalLong);
            }
        }
    }
}

void blinkLed(unsigned long thisDelay){
  unsigned long currentMillis = millis();
  if((currentMillis - previousMillis) > thisDelay){
    previousMillis = currentMillis;
    if(ledState == LOW){
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}
