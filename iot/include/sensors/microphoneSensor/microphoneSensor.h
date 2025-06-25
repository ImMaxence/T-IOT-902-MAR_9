#ifndef MICROPHONESENSOR_H
#define MICROPHONESENSOR_H

#include <Arduino.h>
#include "sensorData/sensorData.h"
#include <driver/i2s.h>
#include <cmath>

// Configuration I2S pour SPH0645
#define I2S_NUM_MIC         I2S_NUM_0
#define I2S_SAMPLE_RATE     16000
#define I2S_BUFFER_SIZE     512

// Pins selon votre schéma
#define I2S_BCLK_PIN        13  // Bit Clock
#define I2S_LRC_PIN         14  // Left/Right Clock
#define I2S_DOUT_PIN        33  // Data Out

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
