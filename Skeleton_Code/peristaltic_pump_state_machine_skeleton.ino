//Include statements
#include <Arduino.h>

//TODO: need to change these pins in the final
//input pins
#define EC_PROBE A3

//output pins
#define FERTILIZER_PUMP 5
#define SOLENOID_PUMP 4

//universal values
float EC_LOWER = 2.0;
float EC_HIGH = 4.0;

//FUNCTIONS:
void fsmPeristalticPump();
float ECProbe(); //this will need to be changed 
void belowThreshold();
void aboveThreshold();

void setup() {
  // put your setup code here, to run once:
  pinMode(FERTILIZER_PUMP, OUTPUT);
  //include pinModes for the EC_PROBE

}

void loop() {
  // put your main code here, to run repeatedly:
  fsmPeristalticPump();
}

void fsmPeristalticPump() {
  static int peristalticPumpState = 0;

  switch (peristalticPumpState) {
    case 0: //no reading EC = 0 no water.
      //for now do nothing.
      //If we calculate the flow rate of the water pump we can have this run at a specific amount
      //  so that we can equalize the EC immediately

      if (ECProbe() < EC_LOWER) {
        peristalticPumpState = 1; //below the threshold
      }
      else if (ECProbe() > EC_HIGH) {
        peristalticPumpState = 2; //above the threshold
      }
      else if (EC_LOWER < ECProbe() < EC_HIGH) {
        peristalticPumpState = 3; // in the threshold
      }
      break;
    case 1: //below the threshold
      belowThreshold();
      
      if (ECProbe() == 0) {
        peristalticPumpState = 0;
      }
      else if (EC_LOWER < ECProbe() < EC_HIGH) {
        peristalticPumpState = 3;
      }
      else if (ECProbe() > EC_HIGH) {
        peristalticPumpState = 2;
      }
      break;
    case 2: //above the threshold
      aboveThreshold();

      if (ECProbe() == 0) {
        peristalticPumpState = 0;
      }
      else if (EC_LOWER < ECProbe() < EC_HIGH) {
        peristalticPumpState = 3; 
      }
      else if (ECProbe() < EC_LOWER) {
        peristalticPumpState = 1;
      }
      break;
    case 3: // in the threshold
      //do nothing just keep checking if statements
      if (ECProbe() == 0) {
        peristalticPumpState = 0;
      }
      else if (ECProbe() < EC_LOWER) {
        peristalticPumpState = 1;
      }
      else if (ECProbe() > EC_HIGH) {
        peristalticPumpState = 2;
      }
      break;
  }
}

float ECProbe() { //this will need to be changed {
  return;
}

void belowThreshold() {
  while (ECProbe() < EC_LOWER) {
    analogWrite(FERTILIZER_PUMP, 85);
    delay(2000);
  }
}

void aboveThreshold() {
  while (ECProbe() > EC_HIGH) {
    digitalWrite(SOLENOID_PUMP, HIGH);
    delay(2000);
  }
}
