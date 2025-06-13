// #include <TinyGPS++.h>
// #include "SensorData.h"

// TinyGPSPlus gps;
// HardwareSerial gpsSerial(1); // UART1

// void setupGPS();
// void loopGPS();
// void printSensorDataGps(SensorData data);

#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include "SensorData.h"

// Déclaration externe (pas de création ici)
extern TinyGPSPlus gps;
extern HardwareSerial gpsSerial;

void setupGPS();
void loopGPS();
void printSensorDataGps(SensorData data);

#endif