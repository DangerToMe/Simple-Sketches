//Sketch to operate 3 stepper motors using shift registers (74HC595)
//Part of a larger project I am working on.

const int latchPin = 3; //ST_CP of 74HC595 (12)
const int clockPin = 5; //SH_CP of 74HC595 (11)
const int dataPin = 4; //DS 0f 74HC595 (14)

unsigned long stepperSpeedFast = 5; //Lower is faster. 5 is probably too fast for my steppers
unsigned long stepperSpeedSlow = 15; //Higher is slower
unsigned long previousMillis = 0;

enum {clearRegister,
      runStepper1Clockwise,
      runStepper1CounterClockwise,
      runStepper2Clockwise,
      runStepper2CounterClockwise,
      runStepper3Clockwise,
      runStepper3CounterClockwise
     };

int currentStage;
int stepper1_Array[] = {B10100000, B01100000, B01010000, B10010000};
int stepper2_Array[] = {B00001010, B00000110, B00000101, B00001001};
int stepper3_Array[] = {B00001010, B00000110, B00000101, B00001001};

int useThisArray;
int stepPulse = 0;
int registerCleared = 0;

//used for testing at this time
const int stepsPerRevolution = 2048;
int stepCount = 0;

void setup() {
  //Serial.begin(9600); //remove or comment out for final code
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, HIGH);
}//end setup

void loop() {
  //Serial.println(currentStage); //just to see where it's at during testing
  switch (currentStage) {
    case clearRegister:
      //in shiftRegister(0, 0, 0)
      //the first 0 denotes which stepper is being controlled
      //the second 0 is forward(1) or reverse(2)
      //the third is the speed of the stepper
      shiftRegister(0, 0, 0);
      break;

    case runStepper1Clockwise:
      shiftRegister(1, 1, stepperSpeedSlow);
      break;

    case runStepper1CounterClockwise:
      shiftRegister(1, 2, stepperSpeedFast);
      break;

    case runStepper2Clockwise:
      shiftRegister(2, 1, stepperSpeedSlow);
      break;

    case runStepper2CounterClockwise:
      shiftRegister(2, 2, stepperSpeedFast);
      break;

    case runStepper3Clockwise:
      shiftRegister(3, 1, stepperSpeedFast);
      break;

    case runStepper3CounterClockwise:
      shiftRegister(3, 2, stepperSpeedFast);
      break;
  }//end switch
 
  test();
 
}//end loop

void shiftRegister(int thisMotor, int thisDirection, unsigned long thisDelay) {
  if (thisMotor == 0 && registerCleared == 0) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    registerCleared = 1;
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= thisDelay) {
      if (stepPulse > 3) {
        stepPulse = 0; //reset stepPulse
      }//end if stepPulse

      int thisIndex;

      if (thisDirection == 2) {
        thisIndex = 3 - stepPulse; //reverse the stepPulse
      } else {
        thisIndex = stepPulse;
      }//end if/else

      if (thisMotor == 1) {
        useThisArray = stepper1_Array[thisIndex];
      } else if (thisMotor == 2) {
        useThisArray = stepper2_Array[thisIndex];
      } else if (thisMotor == 3) {
        useThisArray = stepper3_Array[thisIndex];
      }//end if thisMotor

      previousMillis = currentMillis;
      digitalWrite(latchPin, LOW);
      if (thisMotor == 1 || thisMotor == 2) {
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, useThisArray);
      } else if (thisMotor == 3) {
        shiftOut(dataPin, clockPin, MSBFIRST, useThisArray);
        shiftOut(dataPin, clockPin, MSBFIRST,  0);
      }
      digitalWrite(latchPin, HIGH);
      stepPulse++;
      stepCount++;//for testing. Remove in final project
    }
  }
}

void test() { //
  if (currentStage == clearRegister) {
    delay(5000);
    stepCount = 0;
    currentStage = runStepper1Clockwise;
  } else if (stepCount == stepsPerRevolution) {
    if (currentStage == runStepper1Clockwise) {
      stepCount = 0;
      currentStage = runStepper1CounterClockwise;
    } else if (currentStage == runStepper1CounterClockwise) {
      stepCount = 0;
      currentStage = runStepper2Clockwise;
    } else if (currentStage == runStepper2Clockwise) {
      stepCount = 0;
      currentStage = runStepper2CounterClockwise;
    } else if (currentStage == runStepper2CounterClockwise) {
      stepCount = 0;
      currentStage = runStepper3Clockwise;
    } else if (currentStage == runStepper3Clockwise) {
      stepCount = 0;
      currentStage = runStepper3CounterClockwise;
    } else if (currentStage == runStepper3CounterClockwise) {
      stepCount = 0;
      registerCleared = 0;
      currentStage = clearRegister;
    }
  }
}

