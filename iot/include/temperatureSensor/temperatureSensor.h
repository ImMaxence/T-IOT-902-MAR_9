#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Adafruit_BMP280.h>
#include "SensorData.h"

class TemperatureSensor {
public:
  TemperatureSensor();
  void setup();
  void readSensorData();
  void printSensorData(SensorData data);

private:
  Adafruit_BMP280 bmp;
};

#endif
