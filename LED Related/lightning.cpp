/*
    The Imperfect Storm
    Flashes an LED to simulate lightning
    >>> Currently Untested <<<
    Written for the Arduino Uno
    by DangerToMyself 
    September 25, 2019
    
    Feel free to copy, expand upon, modify, or use as is. But there are 
    probably better scripts with similar results. I'm still learning this stuff.
    Once tested, and bugs worked out, this will become part of a larger
    program to control lighting on my 120 gallon freshwater tank. Future
    modifications of this code may incorporate audible thunder and code 
    to monitor the weather via the internet. I, also, have in mind to add an
    LDR mounted outside to control how bright the lights are based on the
    brightness of the sky.
*/

int ledPin = 5;
int ledState = LOW;  //start with LED off
int startLightning = 0;
int strikeCount = 0;
int strikeNum = 0;
int minFlashes = 3; //change to MINIMUM number of flashes
int maxFlashes = 10; //change to MAXIMUM number of flashes

unsigned long flashDelay;
unsigned long strikeDelay;
unsigned long previousMillis;
unsigned long previousStrikeMillis;

void setup(){
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, ledState); //starts out LOW
	//insert randomSeed code here
	getFlashTiming(); //pre-select first flash length
	getStrikeTiming(); //pre-select first wait time until flash sequence
}

void loop(){
	startStorm(); //lets get stawted
}

void startStorm(){
	unsigned long currentMillis = millis(); 
    if(currentMillis - previousStrikeMillis >= strikeDelay){
    	//time between  STRIKES has exceeded the current wait time
	    //set variables and call functions to set up the next strike
    	previousStrikeMillis = currentMillis; 
        getStrikeTiming();
        startLightning = 1;
        //pick a random number of strikes
        strikeNum = random(minFlashes, maxFlashes)*2; // double to have even number On/Off
     }
     flashLightning(); //call to function that actually operates the LED
}

void flashLightning(){
	if(startLightning == 1){ //if one, begin (or continue) flash sequence
	    unsigned long currentMillis = millis(); 
        if(currentMillis - previousMillis >= flashDelay){
        	//time between FLASHES has elapsed
	        //set variables and call functions to set up next flash
             previousMillis = currentMillis;
             getFlashTiming();
             
             //turn LED off/on
             if(ledState == LOW){
              	ledState = HIGH;
             } else {
              	ledState = LOW;
             }
             digitalWrite(ledPin, ledState);
             
             //finished with sequence?
             if(strikeCount == strikeNum){
              	strikeCount = 0;
                  startLightning = 0;
             } else {
             	strikeCount++;
             }
         }
     }
}

void getStrikeTiming(){
	// set next strike between 5000 and 50000 millis
	// ( 5 seconds to 50 seconds)
	strikeDelay = 500UL * random(10,100);
	}

void getFlashTiming(){
	//set flashDelay to a random number between 10 and 100
	 flashDelay = 1UL * random(10,100);
}
