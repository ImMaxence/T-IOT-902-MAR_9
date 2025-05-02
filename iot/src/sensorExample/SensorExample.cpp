#include "lora/LoRaInstance.h"
#include "SensorExample.h"
#include "SensorData.h"

SensorExample::SensorExample()
{
}

void SensorExample::readSensor()
{
    SensorData data = {
        .name = "example",
        .value = 123,
        .unit = "unit",
        .timestamp = 0}; // Laisser le timestamp à 0, il est automatiquement set dans loRaTransmitter.addData()

    loRaTransmitter.addData(data);
}