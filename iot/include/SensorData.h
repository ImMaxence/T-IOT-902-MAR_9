#include <Arduino.h>

#ifndef SENSORDATA_H
#define SENSORDATA_H

struct SensorData
{
    String name;
    float value;
    String unit;
    long timestamp;
};

#endif
