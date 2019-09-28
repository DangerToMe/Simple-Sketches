

/*
  A simple traffic light script
  Written for the Arduino Uno
  by DangerToMyself
  September 27, 2019

  Activates 6 LEDs to simulate a 2 way traffic light
  I have no use for this script. I just wrote it as 
  practice. Once again, there are probably better 
  scripts out there for this purpose.

  un-comment Serial.print calls for testing
  
  light conditions
    Red both directions for 2 seconds
    North-South goes green for 20 seconds
    North-South goes yellow for 5 seconds
    Red both directions for 2 seconds
    East-West goes green for 20 seconds
    East_west goes yellow for 5 seconds
      back to top
*/

int NSredLEDpin = 3;
int NSyellowLEDpin = 4;
int NSgreenLEDpin = 5;
int EWredLEDpin = 6;
int EWyellowLEDpin = 7;
int EWgreenLEDpin = 8;
int nextLight = 0;

enum {bothRed1, NSgreen, NSyellow, bothRed2, EWgreen, EWyellow};

// Change times to suit
unsigned long lightTimes[] = {2000, 20000, 5000, 2000, 20000, 5000}; //timing in mlliseconds
unsigned long previousMillis;

void setup() {
  //Serial.begin(57600);
  for (int i = 3; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  switchLeds();
}

void switchLeds() {
  switch (nextLight) {
    case bothRed1:
      digitalWrite(NSredLEDpin, HIGH);
      digitalWrite(EWredLEDpin, HIGH);
      digitalWrite(EWyellowLEDpin, LOW);
      startClock(lightTimes[bothRed1]);
      //Serial.println("Both RED");
      break;
    case NSgreen:
      digitalWrite(NSredLEDpin, LOW);
      digitalWrite(NSgreenLEDpin, HIGH);
      startClock(lightTimes[NSgreen]);
      //Serial.println("North-South GREEN");
      break;
    case NSyellow:
      digitalWrite(NSgreenLEDpin, LOW);
      digitalWrite(NSyellowLEDpin, HIGH);
      startClock(lightTimes[NSyellow]);
      //Serial.println("North-South YELLOW");
      break;
    case bothRed2:
      digitalWrite(NSredLEDpin, HIGH);
      startClock(lightTimes[bothRed2]);
      //Serial.println("Both RED");
      break;
    case EWgreen:
      digitalWrite(EWredLEDpin, LOW);
      digitalWrite(EWgreenLEDpin, HIGH);
      startClock(lightTimes[EWgreen]);
      //Serial.println("East-West GREEN");
      break;
    case EWyellow:
      digitalWrite(EWgreenLEDpin, LOW);
      digitalWrite(EWyellowLEDpin, HIGH);
      startClock(lightTimes[EWyellow]);
      //Serial.println("East-West YELLOW");
      break;
  }
}

void startClock(unsigned long thisDelay) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= thisDelay) {
    previousMillis = currentMillis;
    nextLight++;
    if (nextLight == 6) {
      nextLight = 0;
    }
  }
}
