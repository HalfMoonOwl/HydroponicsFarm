#include "Arduino.h"
#include "Solenoid.h"

//float EC_LOW = 2.0;
//float EC_HIGH = 4.0;
extern float EC_LOW;
extern float EC_HIGH;

int SolenoidFSM(float currentEC, int Pin){
  static int ECState = 0;
//  currentEC = Read(EC_Sensor);    // Need to initialize it and read in a value still. 
  switch (ECState) {
    case 0:   // Do NOT run motor. Waiting state
      if(currentEC >= EC_HIGH || currentEC <= 0){   // Too much fertalizer, turn water on.
        ECState = 1;
        digitalWrite(Pin, HIGH);
        delay(1000);
        digitalWrite(Pin, LOW);
      }
    break;

    case 1:   // Run motor
      if (currentEC > 0 && currentEC < EC_HIGH){ //Plant has water turn off
        ECState = 0;
        digitalWrite(Pin, LOW);
      }      
    break;
  }
  return(ECState);

}
