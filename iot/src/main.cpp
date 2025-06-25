#include <Arduino.h>
#include <Wire.h>
#include "./loRa/loRaTransmitter/loRaTransmitter.h"
#include "sensorData/sensorData.h"
#include "sensors/temperatureSensor/temperatureSensor.h"
#include "sensors/gpsSensor/gpsSensor.h"
#include "sensors/microphoneSensor/microphoneSensor.h"

LoRaTransmitter loRaTransmitter;

GPSSensor gpsSensor;
TemperatureSensor temperatureSensor;
MicrophoneSensor microphoneSensor;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Wire.begin(21, 22);
    Serial.println("▶ setup démarré");

    loRaTransmitter.begin(10000);
    gpsSensor.setup();
    temperatureSensor.setup();
    microphoneSensor.setup();
}

void loop()
{
    temperatureSensor.readSensorData();
    gpsSensor.readSensorData();
    microphoneSensor.readSensorData();

    if (loRaTransmitter.canSendMessage())
    {
        Serial.println(loRaTransmitter.sendMessage() ? "-----------message envoyé-----------" : "-----------error lors de l'envoi-----------");
    }
    delay(5000);
}
