#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

//*****************Stuff for EC Probe*************************//
#include "ECProbe.h"

//Pins
int ECPin = A0;
int ECGround = A1;
int ECPower = A4;
int R1 = 1000; //resistor used for the EC probe
int Ra = 25; //pin resistance

#define ONE_WIRE_BUS 10          // Data wire For Temp Probe is plugged into pin 10 on the Arduino
const int TempProbePossitive =8;  //Temp Probe power connected to pin 9
const int TempProbeNegative=9;    //Temp Probe Negative connected to pin 8

//Raw data and set up
OneWire oneWire(ONE_WIRE_BUS);// Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);// Pass our oneWire reference to Dallas Temperature.
//*******************End of EC Probe stuff*********************//

//********************Solenoid Pump Stuff**********************//
#include "Solenoid.h"
int solenoidPin = 7; 

//******************Peristaltic Pump stuff*********************//
#include "PeristalticPump.h"
int peristalticPump = 6;

//********************Main function stuff**********************//
float mainEC = 0.0;

//**********************Global Variables***********************//
float EC_LOW = 2.0;
float EC_HIGH = 4.0;

void setup() {
  // put your main code here, to run repeatedly:
  Serial.begin(9600);
  //*****************For ECProbe******************************//
  pinMode(TempProbeNegative , OUTPUT ); //seting ground pin as output for tmp probe
  digitalWrite(TempProbeNegative , LOW );//Seting it to ground so it can sink current
  pinMode(TempProbePossitive , OUTPUT );//ditto but for positive
  digitalWrite(TempProbePossitive , HIGH );
  pinMode(ECPin,INPUT);
  pinMode(ECPower,OUTPUT);//Setting pin for sourcing current
  pinMode(ECGround,OUTPUT);//setting pin for sinking current
  digitalWrite(ECGround,LOW);//We can leave the ground connected permanantly
 
  delay(100);// gives sensor time to settle
  sensors.begin();
  delay(100);
  R1=(R1+Ra);// Taking into acount Powering Pin Resitance

  //*******************Solenoid Pump**************************//
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  mainEC = GetEC(ECPower, ECPin, ONE_WIRE_BUS, sensors, Ra, R1);
  PrintReadings();
  SolenoidFSM(mainEC, solenoidPin);
  PeristalticPumpFSM(mainEC, peristalticPump);
  
}
