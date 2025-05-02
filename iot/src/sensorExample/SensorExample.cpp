#include "lora/LoRaInstance.h"
#include "SensorExample.h"
#include "SensorData.h"

SensorExample::SensorExample() {

}

void SensorExample::readSensor() {
    SensorData data = {
        .name = "example",
        .value = 123,
        .unit = "unit",
        .timestamp = 0
    };

    loRaTransmitter.addData(data);
}