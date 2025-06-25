#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include "sensorData/sensorData.h"

#define RX_PIN 34
#define TX_PIN 12

class GPSSensor {
public:
  GPSSensor();
  void setup();
  void readSensorData();
  void printSensorDataGps(SensorData data);

private:
  TinyGPSPlus gps;
  HardwareSerial gpsSerial;
};

#endif
