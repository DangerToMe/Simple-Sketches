/*
    The Imperfect Storm
    Flashes an LED to simulate lightning
    Written for the Arduino Uno
    by DangerToMyself
    September 25, 2019
    
    I am very pleased with the results this script produces as I'm still 
    learning this stuff. Feel free to copy, expand upon, modify, or use 
    as is. But there are probably better scripts with similar results. 
    This will become part of a larger program to control lighting on my 
    120 gallon freshwater tank. Future modifications of this code may 
    incorporate audible thunder and code to monitor the weather via the 
    internet. I, also, have in mind to add an LDR mounted outside to 
    control how bright the lights are based on the brightness of the sky.
*/

int ledPin = 5;
int ledState = LOW;  //start with LED off
int startLightning = 0;
int strikeCount = 0;
int strikeNum = 0;
int minFlashes = 3; //change to MINIMUM number of flashes
int maxFlashes = 20; //change to MAXIMUM number of flashes
int pickedDigits[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

String myString;

unsigned long flashDelay;
unsigned long strikeDelay;
unsigned long previousMillis;
unsigned long previousStrikeMillis;

void setup() {
  Serial.begin(57600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState); //starts out LOW

  // There are concerns about reading A0 as not really
  // being all that random. I've added a bit of code
  // that >"I believe"< helps add to the randomness.
  randomSeed(analogRead(A0));
  for (int i = 0; i < 10; i++) {
    for (int x = 0; x < 4; x++) {
      int myRandDigit  = random(0, 9);
      myString = myString + myRandDigit;
    }
    pickedDigits[i] = myString.toInt();
    myString = String("");
  }
  int mySeed = pickedDigits[random(0, 10)];
  randomSeed(mySeed);
  getFlashTiming(); // pre-select first flash length
  getStrikeTiming(); // pre-select first wait time until flash sequence
}

void loop() {
  startStorm(); // lets get stawted
}

void startStorm() {
  // The strikeDelay is initiated in setup. It can take
  // up to 50 seconds to activate the first sequence
  unsigned long currentMillis = millis();
  if (currentMillis - previousStrikeMillis >= strikeDelay) {
    // Time between  STRIKES has exceeded the current wait time
    // Set variables and call functions to set up the next strike
    previousStrikeMillis = currentMillis;
    getStrikeTiming();
    startLightning = 1;
    // Pick a random number of flashes for next strike
    strikeNum = random(minFlashes, maxFlashes) * 2; // Double to have even number On/Off
  }
  flashLightning(); // Call to function that actually operates the LED
}

void flashLightning() {
  if (startLightning == 1) { // If one, begin (or continue) flash sequence
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= flashDelay) {
      //time between FLASHES has elapsed
      //set variables and call functions to set up next flash
      previousMillis = currentMillis;
      getFlashTiming(); // Reset the flashDelay

      //turn LED off/on
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPin, ledState); // Write LED pin high or low

      //finished with sequence?
      if (strikeCount == strikeNum) { // If finished 
        strikeCount = 0;
        startLightning = 0;
        digitalWrite(ledPin, LOW);
      } else { // If not finished
        strikeCount++;
      }
    }
  }
}

void getStrikeTiming() {
  // set next strike between 5000 and 50000 millis
  // ( 5 seconds to 50 seconds)
  //chose 5 seconds because there is the possibility
  //of 20 flashes at a maximum of 100 milliseconds. That's
  //2 seconds. Plus the possibility of 20 off times
  //totalling 2 seconds. But a 4 second sequence is
  //highly unlikely.

  // Get random number and multiply by 500UL
  // causing strikeDelay to be an unsigned long.
  strikeDelay = 500UL * random(10, 100); 

  // Remove or comment out for final use
  // Just here to see when things re going to happen
  //Serial.print("Next strike in ");
  //Serial.print(strikeDelay);
  //Serial.println(" milliseconds");
}

void getFlashTiming() {
  // Set flashDelay to a random number between 10 and 100
  // multiply by 1UL causing flashDelay to be an unsigned long.
  flashDelay = 1UL * random(10, 100);
}
