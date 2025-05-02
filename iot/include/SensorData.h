#include <Arduino.h>

#ifndef SENSORDATA_H // Si SENSORDATA_H n'a pas encore été défini
#define SENSORDATA_H

struct SensorData
{
    String name;
    float value;
    String unit;
    long timestamp;
};

#endif // SENSORDATA_H
