#ifndef PERISTALTICPUMP_H
#define PERISTALTICPUMP_H

extern float EC_LOW;
extern float EC_HIGH;

int PeristalticPumpFSM(float currentEC, int Pin);

#endif
