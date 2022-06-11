#ifndef ECPROBE_H
#define ECPROBE_H

#include <OneWire.h>
#include <DallasTemperature.h>

float GetEC(int Pin1, int Pin2, OneWire TheWire, DallasTemperature sensors, int Ra, int R1);
void PrintReadings();

#endif
