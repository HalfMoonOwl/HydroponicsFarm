#include <Arduino.h>

extern float EC_LOW;
extern float EC_HIGH;

//float EC_LOW = 2.0;
//float EC_HIGH = 4.0;

void PeristalticPumpFSM(float currentEC, int Pin) {
  static int peristalticPumpState = 0;
    Serial.print("Peristaltic Pump State: ");
    Serial.println(peristalticPumpState);
    

  switch (peristalticPumpState) {
    case 0: //no reading EC = 0 no water.
      //for now do nothing.
      //If we calculate the flow rate of the water pump we can have this run at a specific amount
      //  so that we can equalize the EC immediately

      if (currentEC < EC_LOW) {
        peristalticPumpState = 1; //below the threshold
      }
      else if (currentEC > EC_HIGH) {
        peristalticPumpState = 2; //above the threshold
      }
      else if (EC_LOW < currentEC <= EC_HIGH) {
        peristalticPumpState = 3; // in the threshold
      }
      break;
    case 1: //below the threshold
      digitalWrite(Pin, HIGH);
      delay(3200);
      digitalWrite(Pin, LOW);
      delay(1500);
      
      if (currentEC == 0) {
        peristalticPumpState = 0;
      }
      else if (EC_LOW < currentEC <= EC_HIGH) {
        peristalticPumpState = 3;
      }
      else if (currentEC > EC_HIGH) {
        peristalticPumpState = 2;
      }
      break;
    case 2: //above the threshold
      digitalWrite(Pin, LOW);

      if (currentEC == 0) {
        peristalticPumpState = 0;
      }
      else if (EC_LOW < currentEC <= EC_HIGH) {
        peristalticPumpState = 3; 
      }
      else if (currentEC < EC_LOW) {
        peristalticPumpState = 1;
      }
      break;
    case 3: // in the threshold
      //do nothing just keep checking if statements
      if (currentEC == 0) {
        peristalticPumpState = 0;
      }
      else if (currentEC < EC_LOW) {
        peristalticPumpState = 1;
      }
      else if (currentEC > EC_HIGH) {
        peristalticPumpState = 2;
      }
      break;
  }
}
