// 


#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Adafruit_BMP280.h>
#include "SensorData.h"

extern Adafruit_BMP280 bmp;

void setupTemperatureSensor();
void loopTemperatureSensor();
void printSensorDataTemp(SensorData data);

#endif