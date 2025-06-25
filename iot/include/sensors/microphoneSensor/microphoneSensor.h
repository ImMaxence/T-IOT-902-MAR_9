#ifndef MICROPHONESENSOR_H
#define MICROPHONESENSOR_H

#include <Arduino.h>
#include "sensorData/sensorData.h"
#include <driver/i2s.h>
#include <cmath>

class MicrophoneSensor {
public:
    MicrophoneSensor();
    void setup();
    void readSensorData();
    void printSensorData(SensorData data);

private:
    bool initialized;
    float lastSoundLevel;
    
    // Méthodes privées
    bool initializeI2S();
    float readAmplitude();
    float convertToDecibels(float amplitude);
    float calculateRMS(int32_t* samples, int count);
    
    // Constantes
    static const float CALIBRATION_OFFSET;
    static const int BITS_SHIFT_SPH0645;
};

#endif
