#include "Arduino.h"
#include "Solenoid.h"

//float EC_LOW = 2.0;
//float EC_HIGH = 4.0;
extern float EC_LOW;
extern float EC_HIGH;

int SolenoidFSM(float currentEC, int Pin){
  static int ECState = 0;
  Serial.print("Solenoid State: ");
    Serial.println(ECState);
    Serial.println(currentEC);

//  currentEC = currentEC;    // Need to initialize it and read in a value still. 
  switch (ECState) {
    case 0:   // Do NOT run motor. Waiting state
    digitalWrite(Pin, LOW);
      if(currentEC >= EC_HIGH || currentEC < 0.5){   // Too much fertalizer, turn water on.
        ECState = 1;
      }
    break;

    case 1:   // Run motor
    digitalWrite(Pin, HIGH);
      if (currentEC > 0.5 && currentEC < EC_HIGH){ //Plant has water turn off
        ECState = 0;
      }      
    break;
  }
  return(ECState);

}
